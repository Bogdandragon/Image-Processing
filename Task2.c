#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct {
    bmp_fileheader fileheader;
    bmp_infoheader infoheader;
    Pixel** bitmap;
} Image;

Image* insertImage(Image *dest, Image *target, long long x, long long y) {
    long long i = 0, j = 0, k = target->infoheader.height - 1, l = 0;
    for (i = dest->infoheader.height - x - 1; i >= 0 && k >= 0; i--) {
        l = 0;
        for (j = y; j < dest->infoheader.width && l < target->infoheader.width; j++) {
            if (i >= 0 && i < dest->infoheader.height && j >= 0 && j < dest->infoheader.width) {
                if (k >= 0 && k < target->infoheader.height && l >= 0 && l < target->infoheader.width)
                    dest->bitmap[i][j] = target->bitmap[k][l];
            }
            l += 1;
        }
        k -= 1;
    }
    free(target);
    return dest;
}
