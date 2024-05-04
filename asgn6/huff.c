#include "bitwriter.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    //clearing elements in histogram array
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    //holds file size and initializes to 0
    uint64_t size = 0;

    //reads bytes from inbuf uintil it reaches the end of file

    //uint function form .a file to r
    //false when file has ended
    //if not false continue loop
    uint8_t byte;
    while (read_uint8(inbuf, &byte)) {
        //incrementing each element of the array
        histogram[byte]++;
        //incrementing file size
        size++;
    }

    //applying hack
    ++histogram[0x00];
    ++histogram[0xff];

    return size;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *queue = pq_create();
    //resetting just to be safe
    *num_leaves = 0;

    for (uint16_t symbol = 0; symbol < 256; symbol++) {
        if (histogram[symbol] > 0) {
            Node *node = node_create(symbol, histogram[symbol]);
            enqueue(queue, node);

            //* before ->dereferencing then incrementing
            (*num_leaves)++;
        }
    }

    //Huffman Coding Algorithm
    while (!pq_size_is_1(queue)) {

        Node *left;
        Node *right;
        dequeue(queue, &left);
        dequeue(queue, &right);

        Node *new_node = node_create(0, left->weight + right->weight);
        new_node->left = left;
        new_node->right = right;

        enqueue(queue, new_node);
    }

    Node *root;
    dequeue(queue, &root);

    pq_free(&queue);
    return root;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {

    if (node->left == NULL && node->right == NULL) {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    } else {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= ((uint64_t) 1 << code_length);
        fill_code_table(code_table, node->right, code, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {

    if (node->left != NULL && node->right != NULL) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {

    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    huff_write_tree(outbuf, code_tree);

    uint8_t b = 0;

    while (read_uint8(inbuf, &b)) {

        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;

        //still need this - within while loop
        for (int8_t j = 0; j <= code_length - 1; j++) {
            uint8_t bit = (code >> j) & 1;
            bit_write_bit(outbuf, bit);
        }
    }
}

void free_tree(Node *node) {
    if (node == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);

    node_free(&node);
}

int main(int argc, char **argv) {

    int op = 0;
    char *infile = NULL;
    char *outfile = NULL;
    Buffer *inbuf = NULL;
    BitWriter *outbuf = NULL;
    double histogram[256];
    uint16_t num_leaves = 0;

    while ((op = getopt(argc, argv, OPTIONS)) != -1) {
        switch (op) {
        case 'i': {
            //buffers need to do file opening
            infile = optarg;
            inbuf = read_open(infile);
            if (inbuf == NULL) {
                printf("Error occured opening file, please enter a valid input file.");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 'o': {
            outfile = optarg;
            outbuf = bit_write_open(outfile);
            break;
        }
        case 'h': {
            fprintf(stdout,
                "Usage: huff -i infile -o outfile\n huff -v -i infile -o outfile\nhuff -h\n");
            break;
        }
        }
    }

    //calling functions
    //intermediate steps
    //free buffer and close files

    if (infile == NULL || outfile == NULL) {
        printf("Error opening input or output file, one not assigned. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    uint64_t filesize = fill_histogram(inbuf, histogram);

    Node *code_tree = create_tree(histogram, &num_leaves);

    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);
    //fill_code_table(code_table, node, code, code_length);

    read_close(&inbuf);
    inbuf = read_open(infile);

    huff_compress_file(outbuf, inbuf, filesize, num_leaves, code_tree, code_table);

    //do we need to call node_free on code_tree? -> you will eventually free this -> last in the recursive function
    // write  recursive function to handle both left and right child and free individual node recursivley

    free_tree(code_tree);

    read_close(&inbuf);
    bit_write_close(&outbuf);

    return 0;
}
