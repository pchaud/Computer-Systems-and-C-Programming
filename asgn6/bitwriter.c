#include "bitwriter.h"

#include "io.h"

#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    Buffer *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    //allocate a BitWriter object
    BitWriter *buf = malloc(sizeof(BitWriter));
    //create buffer using write_open function
    Buffer *underlying_stream = write_open(filename);

    //reports an error and exits out of the program if the buffer/opening the file cannot be executed
    if (buf == NULL) {
        fprintf(stderr, "Failed to allocate memory to BitWriter buffer.\n");
        return NULL;
    }

    if (underlying_stream == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        free(buf);
        return NULL;
    }

    buf->underlying_stream = underlying_stream;

    //are these necessary?
    buf->byte = 0; //initializing byte and bit_position
    buf->bit_position = 0;

    return buf;
}

void bit_write_close(BitWriter **pbuf) {
    BitWriter *buf = *pbuf;
    if (buf->bit_position > 0) {
        write_uint8(buf->underlying_stream, buf->byte);
    }
    write_close(&buf->underlying_stream);
    free(buf);
    *pbuf = NULL;
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        write_uint8(buf->underlying_stream, buf->byte);
        buf->byte = 0x00;
        buf->bit_position = 0;
    }
    if (bit & 1) {
        buf->byte |= (bit & 1) << buf->bit_position;
    }

    buf->bit_position += 1;
}

void bit_write_uint8(BitWriter *buf, uint8_t byte) {

    for (int i = 0; i < 8; i++) {
        uint8_t bit = (byte >> i) & 1; //gettng rightmost bit (LSB)
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}
