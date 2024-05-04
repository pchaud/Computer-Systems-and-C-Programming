#include "io.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct buffer Buffer;

struct buffer {
    int fd; // file descriptor from open() or creat()
    int offset;
    int num_remaining; // offset into buffer a[]
        //next valid byte (reading)
        //next empty location (writing)
    uint8_t a[BUFFER_SIZE]; // buffer
};

Buffer *read_open(const char *filename) {

    //opens file
    int open_file = open(filename, O_RDONLY);

    //if opening the file is unsucessful, returns NULL
    if (open_file < 0) {
        return NULL;
    }

    //mallocing the buffer
    Buffer *buffer = malloc(sizeof(Buffer));

    if (buffer == NULL) {
        close(open_file);
        return NULL;
    }

    //returning pointer to new Buffer + setting fd and other struct variables to 0
    buffer->fd = open_file;
    buffer->offset = 0;
    buffer->num_remaining = 0;

    return buffer;
}

void read_close(Buffer **pbuf) {

    close((*pbuf)->fd); //closes files
    free(*pbuf); //frees buffer
    *pbuf = NULL; //setting pointer to buffer to NULL
}

//most basic operation
bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0) {
            printf("Error handling reading operations for uint8 buffer.");
        }
        if (rc == 0) {
            return false; // end of file
        }

        buf->num_remaining = rc;
        buf->offset = 0;
    }

    //storing next byte in the buffer in *x
    *x = buf->a[buf->offset]; //*x = memory location pointed to by x
    buf->offset++; //incrementing to indicate a byte was removed from the buffer
    buf->num_remaining--; //decrements num_remaining as a byte has been removed

    return true;
}

//call uint8 twice
bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t b1, b2;

    if (!read_uint8(buf, &b1)) {
        return false;
    }

    if (!read_uint8(buf, &b2)) {
        return false;
    }

    uint16_t deser = ((uint16_t) b2 << 8) | b1;

    *x = deser;

    return true;
}

//call uint16 twice
bool read_uint32(Buffer *buf, uint32_t *x) {

    uint16_t b1, b2;

    if (!read_uint16(buf, &b1)) {
        return false;
    }

    if (!read_uint16(buf, &b2)) {
        return false;
    }

    uint32_t deser = ((uint32_t) b2 << 16) | b1;

    *x = deser;

    return true;
}

Buffer *write_open(const char *filename) {

    //opens file
    int w_file_open = creat(filename, 0664);

    //if unsuccessful then it returns null
    if (w_file_open < 0) {
        return NULL;
    }

    //otherwise, it will dynamically allocate memory to the new buffer
    Buffer *write_buffer = malloc(sizeof(Buffer));

    //checks if memory allocation was successful or not
    if (write_buffer == NULL) {
        //if it wasn't, the file is closed and NULL is returned
        close(w_file_open);
        return NULL;
    }

    //sets  field to return value from creat() + sets the rest of the fields to 0
    write_buffer->fd = w_file_open;
    write_buffer->offset = 0;
    write_buffer->num_remaining = 0;
    memset(write_buffer->a, 0, sizeof(write_buffer->a));

    return write_buffer;
}

void write_close(Buffer **pbuf) {

    write((*pbuf)->fd, (*pbuf)->a, (*pbuf)->offset);
    close((*pbuf)->fd);
    //free buffer
    free(*pbuf);
    *pbuf = NULL;
}

void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->a;
        int num_bytes = buf->offset;
        do {
            ssize_t rc = write(buf->fd, start, num_bytes); //writing bytes from buffer to file
            if (rc < 0) {
                printf("Error handling write operations.");
                return;
            }
            start += rc; // skip past the bytes that were just written
            num_bytes -= rc; // how many bytes are left?
        } while (num_bytes > 0);
        buf->offset = 0; //resetting buffer since it's already empty at this point
    }

    buf->a[buf->offset] = x; //adding new byte to buf
    buf->offset++; //incrementing offset
}

void write_uint16(Buffer *buf, uint16_t x) {

    //serializes lower byte of x
    write_uint8(buf, (uint8_t) (x & 0xFF));

    //serializes upper byte of x
    write_uint8(buf, (uint8_t) (x >> 8));
}

void write_uint32(Buffer *buf, uint32_t x) {

    //serializes lower 16 bits of x
    write_uint16(buf, (uint16_t) (x & 0xFFFF));

    //serializes upper 16 bits of x
    write_uint16(buf, (uint16_t) (x >> 16));
}
