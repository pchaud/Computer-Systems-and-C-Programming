#include "bmp.h"
#include "io.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

int main(int argc, char **argv) {

    int op = 0;
    char *infile = NULL;
    char *outfile = NULL;

    Buffer *inputBuf = NULL;
    Buffer *outputBuf = NULL;

    BMP *bmp = NULL;

    while ((op = getopt(argc, argv, OPTIONS)) != -1) {
        switch (op) {
        case 'i': {
            infile = optarg;
            inputBuf = read_open(infile);
            if (inputBuf == NULL) {
                printf("colorb:  error reading input file bmps/apples-orig.bmp\n Usage: colorb -i "
                       "infile -o outfile \n colorb -h");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 'o': {
            //need to use write open
            outfile = optarg;
            outputBuf = write_open(outfile);
            break;
        }
        case 'h': {
            fprintf(stdout, "Usage: colorb -i infile -o outfile\n colorb -h");
            exit(EXIT_SUCCESS);
            break;
        }
        }
    }

    //make sure input file and output file both got assigned
    //if readopen returns NULL -> exit
    if (infile == NULL || outfile == NULL) {
        printf("Error opening input or output file, one not assigned. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    bmp = bmp_create(inputBuf);

    //call reduce palette
    bmp_reduce_palette(bmp);

    //write it out
    bmp_write(bmp, outputBuf);

    //bmp free
    bmp_free(&bmp);

    //close files
    read_close(&inputBuf);
    write_close(&outputBuf);

    return 0;
}
