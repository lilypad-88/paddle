#include "img.h"
#include <stdio.h>

void test() {
    Color pixel = {1.0, 1.0, 1.0};
    Image test;
    test.width = 1;
    test.height = 1;
    test.pixels = &pixel;
}

int *png_load(char *path) {
    FILE *f = fopen(path, "rb");
}
