#ifndef IMG_H
#define IMG_H
#include <stdint.h>

typedef struct pdl_Color {
    float r, g, b;
} pdl_Color;

typedef struct pdl_Image {
    int width, height;
    pdl_Color *pixels;
} pdl_Image;

int pdl_png_load(char *path, pdl_Image *img);
void pdl_png_free(pdl_Image *img);
uint32_t pdl_uint32_reverse_endianness(uint32_t *num);

#endif
