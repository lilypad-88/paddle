#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "colors.h"
#include "img.h"

#define PNG_HEADER_SIZE 8

const uint8_t png_header[PNG_HEADER_SIZE] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};

// Confirm PNG header is readable
int validate_png(FILE *file) {
    if (file == NULL) {
        printf(RED "Error: Could not open file\n" RESET);
        return -1;
    }

    uint8_t file_header[PNG_HEADER_SIZE];
    for (int i = 0; i < PNG_HEADER_SIZE; i++) {
        int c = fgetc(file);

        if (c == EOF) {
            printf(RED "Error: Header ended prematurely\n" RESET);
            fclose(file);
            return -1;
        }

        file_header[i] = (uint8_t)c;
    }

    // for (int i = 0; i < PNG_HEADER_SIZE; i++) {
    //     printf("%02x ", file_header[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < PNG_HEADER_SIZE; i++) {
    //     printf("%02x ", png_header[i]);
    // }
    // printf("\n");

    for (int i = 0; i < PNG_HEADER_SIZE; i++) {
        if (file_header[i] != png_header[i]) {
            printf(RED "Error: Header does not match PNG\n" RESET);
            fclose(file);
            return -1;
        }
    }
    printf(GRN "This is a PNG :3\n" RESET);

    return 0;
}

int png_load(char *path, Image *img) {
    FILE *file = fopen(path, "rb");

    if (validate_png(file) != 0) {
        file = NULL;
        return -1;
    }

    fclose(file);

    return 0;
}
