#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "img.h"

#define PNG_HEADER_SIZE 8

const uint8_t png_header[PNG_HEADER_SIZE] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};

typedef struct pngChunk {
    uint32_t length;
    unsigned char type[4];
    uint8_t *data;
    uint8_t crc[4];
} pngChunk;

typedef struct pngIHDRData {
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;
} pngIHDRData;

// Confirm PNG header is readable
int validate_png_header(FILE *file) {
    if (file == NULL) {
        printf(RED "Error: Could not open file\n" RESET);
        return -1;
    }

    uint8_t file_header[PNG_HEADER_SIZE];
    if (fread(file_header, sizeof(uint8_t), PNG_HEADER_SIZE, file) < PNG_HEADER_SIZE) {
        printf(RED "Error: Header ended prematurely\n" RESET);
        return -1;
    }

    for (int i = 0; i < PNG_HEADER_SIZE; i++) {
        if (file_header[i] != png_header[i]) {
            printf(RED "Error: Header does not match PNG\n" RESET);
            return -1;
        }
    }

    return 0;
}

// Parse and pass next chunk. Return <___> when done and -1 on failure
int png_parse_next_chunk(FILE *file, pngChunk *chunk) {
    // Length
    for (int i = sizeof(chunk->length) - 1; i >= 0; i--) {
        int c = fgetc(file);
        if (c == EOF) {
            printf(RED "Error: Chunk length ended prematurely\n" RESET);
            return -1;
        }
        ((uint8_t*) &chunk->length)[i] = (uint8_t) c;
    }

    // Type
    if (fread(chunk->type, sizeof(unsigned char), sizeof(chunk->type), file) != sizeof(chunk->type)) {
        printf(RED "Error: Chunk type ended prematurely\n" RESET);
        return -1;
    }

    // Data
    chunk->data = malloc(chunk->length * sizeof(uint8_t));
    if (fread(chunk->data, sizeof(uint8_t), chunk->length, file) != chunk->length) {
        printf(RED "Error: Chunk data ended prematurely\n" RESET);
        free(chunk->data);
        return -1;
    }


    // CRC
    if (fread(chunk->crc, sizeof(uint8_t), sizeof(chunk->crc), file) != sizeof(chunk->crc)) {
        printf(RED "Error: Chunk crc ended prematurely\n" RESET);
        return -1;
    }

    return 0;
}

// Print chunk details
void png_print_chunk(pngChunk *chunk) {
    printf(CYN "Length" RESET ": %d\n", chunk->length);

    printf(CYN "Type" RESET ": %c%c%c%c\n", chunk->type[0], chunk->type[1], chunk->type[2], chunk->type[3]);

    printf(CYN "Data: " RESET);
    for (uint32_t i = 0; i < chunk->length; i++) {
        printf("%02x ", chunk->data[i]);
    }
    printf("\n");

    printf(CYN "CRC: " RESET);
    for (size_t i = 0; i < sizeof(chunk->crc); i++) {
        printf("%02x ", chunk->crc[i]);
    }
    printf("\n");
}

// Return uint32 with inverted endianess of num
uint32_t pdl_uint32_reverse_endianness(uint32_t *num) {
    uint32_t inverted_num = 0;
    int j = 0;
    for (int i = sizeof(uint32_t) - 1; i >= 0; i--) {
        uint8_t c = ((uint8_t *)num)[j];
        ((uint8_t *) &inverted_num)[i] = c;
        j++;
    }
    return inverted_num;
}

int pdl_png_load(char *path, pdl_Image *img) {
    FILE *file = fopen(path, "rb");

    printf(MAG "Loading %s\n" RESET, path);
    if (validate_png_header(file) != 0) {
        if (file != NULL) {
            fclose(file);
        }
        file = NULL;
        return -1;
    }

    pngChunk chunk;
    if (png_parse_next_chunk(file, &chunk) != 0) {
        fclose(file);
        file = NULL;
        return -1;
    }
    pngIHDRData data;
    // printf("chunk.data: %d\n", *(uint32_t*) *chunk.data);
    data.width = pdl_uint32_reverse_endianness((uint32_t *) chunk.data);
    printf("Width: %d\n\n", data.width);

    png_print_chunk(&chunk);

    // Temp pdl_png_free()
    free(chunk.data);
    chunk.data = NULL;
    fclose(file);

    return 0;
}
