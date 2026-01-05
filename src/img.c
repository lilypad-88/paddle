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

    printf(GRN "This is a PNG :3\n" RESET);
    return 0;
}

// Parse and pass next chunk. Return <___> when done and -1 on failure
int png_parse_next_chunk(FILE *file, pngChunk *chunk) {
    chunk->length = 0;

    for (int i = sizeof(chunk->length) - 1; i >= 0; i--) {
        int c = fgetc(file);
        if (c == EOF) {
            printf(RED "Error: Chunk ended prematurely\n" RESET);
            return -1;
        }
        ((uint8_t*) &chunk->length)[i] = (uint8_t) c;
    }

    printf("Length: %d\n", chunk->length);

    if (fread(chunk->type, sizeof(unsigned char), sizeof(chunk->type), file) != sizeof(chunk->type)) {
        printf(RED "Error: Chunk ended prematurely\n" RESET);
        return -1;
    }

    printf("Type: %c%c%c%c\n", chunk->type[0], chunk->type[1], chunk->type[2], chunk->type[3]);

    // Type
    // for (int i = 0; i < 4; i++) {
    //     chunk->type[i] = fgetc(file);
    // }
    // printf("Type: %c%c%c%c\n", chunk->type[0], chunk->type[1], chunk->type[2], chunk->type[3]);
    //
    // chunk->data = malloc(chunk->length);
    // for (uint32_t i = 0; i < chunk->length; i++) {
    //     chunk->data[i] = fgetc(file);
    //     printf("%02x ", chunk->data[i]);
    // }
    // printf("\n");

    return 0;
}

int pdl_png_load(char *path, pdl_Image *img) {
    FILE *file = fopen(path, "rb");

    if (validate_png_header(file) != 0) {
        if (file != NULL) {
            fclose(file);
        }
        file = NULL;
        return -1;
    }

    pngChunk parsed_chunk;
    if (png_parse_next_chunk(file, &parsed_chunk) != 0) {
        fclose(file);
        file = NULL;
        return -1;
    }

    fclose(file);

    return 0;
}
