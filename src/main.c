#include "img.h"

int main() {
    Image img;

    png_load("assets/example.png", &img);
    png_load("assets/greendolin.png", &img);

    png_load("assets/file.txt", &img);
    png_load("src/img.c", &img);

    return 0;
}
