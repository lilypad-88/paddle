#ifndef IMG_H
#define IMG_H

typedef struct Color {
    float r, g, b;
} Color;

typedef struct Image {
    int width, height;
    Color *pixels;
} Image;

int png_load(char *path, Image *img);
void png_free(Image *img);

#endif
