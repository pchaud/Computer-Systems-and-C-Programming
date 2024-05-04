#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, double weight) {
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL) {
        return NULL;
    }

    node->symbol = symbol;
    node->weight = weight;
    node->code = 0;
    node->code_length = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void node_free(Node **node) {

    free(*node);
    *node = NULL;
}

void node_print_tree(Node *tree, char ch, int indentation) {

    if (tree == NULL)
        return;
    node_print_tree(tree->right, '/', indentation + 3);
    printf("%*cweight = %.0f", indentation + 1, ch, tree->weight);

    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }

    printf("\n");
    node_print_tree(tree->left, '\\', indentation + 3);
}
