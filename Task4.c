#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"
#define N 20001
#define M 3000
#define limit 2000
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

int sameColor(Pixel a, Pixel b) {
    if ((a.b == b.b) && (a.g == b.g) && (a.r == b.r)) {
        return 1;
    } else {
        return 0;
    }
}

/*int hasFilled(int *posX, int *posY, int x, int y, int before){
    int i = 0;
    for(i = 0; i <= before; i++) {
        if (posX[i] == x && posY[i] == y) {
            return 1;
        }
    }
    return 0;
}*/

Image* fill(Image* img, Pixel color, int x, int y) {
    int *posX = (int*) malloc(M * sizeof(int));
    int *posY = (int*) malloc(M * sizeof(int));
    int current = 0, end = 1, i = 0, xCrt = 0, yCrt = 0;
    x = img->infoheader.height - x - 1;
    posX[0] = x;
    posY[0] = y;
    Pixel initColor;
    initColor.r = img->bitmap[x][y].r;
    initColor.g = img->bitmap[x][y].g;
    initColor.b = img->bitmap[x][y].b;
    while (current != end) {
        xCrt = posX[current];
        yCrt = posY[current];
        img->bitmap[xCrt][yCrt].r = color.r;
        img->bitmap[xCrt][yCrt].g = color.g;
        img->bitmap[xCrt][yCrt].b = color.b;
        current += 1;
        if (current == limit) {
            current = 0;
        }
        if (xCrt - 1 >= 0) {
            if (sameColor(img->bitmap[xCrt - 1][yCrt], initColor)) {
                img->bitmap[xCrt - 1][yCrt].r = color.r;
                img->bitmap[xCrt - 1][yCrt].g = color.g;
                img->bitmap[xCrt - 1][yCrt].b = color.b;
                posX[end] = xCrt - 1;
                posY[end] = yCrt;
                end += 1;
                if (end == limit) {
                    end = 0;
                }
            }
        }
        if (yCrt + 1 < img->infoheader.width) {
            if (sameColor(img->bitmap[xCrt][yCrt + 1], initColor)) {
                img->bitmap[xCrt][yCrt + 1].r = color.r;
                img->bitmap[xCrt][yCrt + 1].g = color.g;
                img->bitmap[xCrt][yCrt + 1].b = color.b;
                posX[end] = xCrt;
                posY[end] = yCrt + 1;
                end += 1;
                if (end == limit) {
                    end = 0;
                }
            }
        }
        if (yCrt - 1 >= 0) {
            if (sameColor(img->bitmap[xCrt][yCrt - 1], initColor)) {
                img->bitmap[xCrt][yCrt - 1].r = color.r;
                img->bitmap[xCrt][yCrt - 1].g = color.g;
                img->bitmap[xCrt][yCrt - 1].b = color.b;
                posX[end] = xCrt;
                posY[end] = yCrt - 1;
                end += 1;
                if (end == limit) {
                    end = 0;
                }
            }
        }
        if (xCrt + 1 < img->infoheader.height) {
            if (sameColor(img->bitmap[xCrt + 1][yCrt], initColor)) {
                img->bitmap[xCrt + 1][yCrt].r = color.r;
                img->bitmap[xCrt + 1][yCrt].g = color.g;
                img->bitmap[xCrt + 1][yCrt].b = color.b;
                posX[end] = xCrt + 1;
                posY[end] = yCrt;
                end += 1;
                if (end == limit) {
                    end = 0;
                }
            }
        }
    }
    free(posX);
    free(posY);
    return img;
}
