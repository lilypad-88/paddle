#include "img.h"

int main() {
    pdl_Image img;

    pdl_png_load("assets/example.png", &img);
    pdl_png_load("assets/greendolin.png", &img);

    pdl_png_load("assets/file.txt", &img);
    pdl_png_load("src/img.c", &img);
    pdl_png_load("assets/premature.png", &img);

    return 0;
}
