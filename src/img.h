#ifndef IMG_H
#define IMG_H

typedef struct Color {
    float r, g, b;
} Color;

typedef struct Image {
    int width, height;
    Color *pixels;
} Image;

void test();
int *png_load(char *path);
void png_free(Image *img);

#endif
