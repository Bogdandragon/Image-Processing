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

Image* drawLine(Image* img, Pixel color, unsigned char size,
int x1, int y1, int x2, int y2) {
    int i = 0, j = 0, k = 0, x = 0, y = 0;
    int temp = 0;
    if (abs(x1 - x2) >= abs(y1 - y2)) {
        if (x2 < x1) {
            temp = x2;
            x2 = x1;
            x1 = temp;
            temp = y2;
            y2 = y1;
            y1 = temp;
        }
        for (i = x1; i <= x2; i++) {
            y = (y1 * (x2 - x1) + (i - x1) * (y2 - y1)) / (x2 - x1);
            for (j = (img->infoheader.height - i - 1) - (size/2);
            j <= (img->infoheader.height - i - 1) + (size/2); j++) {
                for (k = y - size/2; k <= y + size/2; k++) {
                    if (j >= 0 && j < img->infoheader.height && k >= 0 && k < img->infoheader.width) {
                        img->bitmap[j][k].r = color.r;
                        img->bitmap[j][k].g = color.g;
                        img->bitmap[j][k].b = color.b;
                    }
                }
            }
        }
    } else {
        if (y2 < y1) {
            temp = y2;
            y2 = y1;
            y1 = temp;
            temp = x2;
            x2 = x1;
            x1 = temp;
        }
        for (i = y1; i <= y2; i++) {
            x = (x1 * (y2 - y1) + (i - y1) * (x2 - x1)) / (y2 - y1);
            for (j = (img->infoheader.height - x - 1) - (size/2);
            j <= (img->infoheader.height - x - 1) + (size/2); j++) {
                for (k = i - size/2; k <= i + size/2; k++) {
                    if (j >= 0 && j < img->infoheader.height && k >= 0 && k < img->infoheader.width) {
                        img->bitmap[j][k].r = color.r;
                        img->bitmap[j][k].g = color.g;
                        img->bitmap[j][k].b = color.b;
                    }
                }
            }
        }
    }
    return img;
}
