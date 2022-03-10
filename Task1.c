#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"
#define five 5
#define six 6
#define seven 7
#define eight 8
#define nine 9
#define ten 10
#define sixteen 16
#define twenty 20
#define twentyfour 24
#define thirty 30
#define forty 40
#define fifty 50

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

Image* editImage(char* path) {
    int len = 0, i = 0, j = 0, k = 0;
    unsigned char* buffer = 0;
    int paddingBytes = 0;
    Image *out = (Image*) malloc(sizeof(Image));
    FILE *f = fopen(path, "rb");
    if (!f)
        printf("oops");
    fseek(f, 0, SEEK_END);
    len = (int) ftell(f);
    rewind(f);

    buffer = (unsigned char*) malloc(len * sizeof(unsigned char));
    fread(buffer, len, 1, f);
    fclose(f);

    out->fileheader.fileMarker1 = buffer[0];
    out->fileheader.fileMarker2 = buffer[1];

    out->fileheader.bfSize = buffer[2] + (buffer[3] << eight) + (buffer[4] << sixteen) + (buffer[five] << twentyfour);
    out->fileheader.unused1 = buffer[six] + (buffer[seven] << eight);
    out->fileheader.unused2 = buffer[eight] + (buffer[nine] << eight);
    out->fileheader.imageDataOffset = buffer[ten] + (buffer[ten + 1] << eight)
        + (buffer[ten + 2] << sixteen) + (buffer[ten + 3] << twentyfour);
    out->infoheader.biSize = buffer[sixteen - 2] + (buffer[sixteen - 1] << eight)
        + (buffer[sixteen] << sixteen) + (buffer[sixteen + 1] << twentyfour);
    out->infoheader.width = buffer[sixteen + 2] + (buffer[sixteen + 3] << eight)
        + (buffer[sixteen + 4] << sixteen) + (buffer[twenty + 1] << twentyfour);
    out->infoheader.height = buffer[twenty + 2] + (buffer[twentyfour - 1] << eight)
        + (buffer[twentyfour] << sixteen) + (buffer[twentyfour + 1] << twentyfour);
    out->infoheader.planes = buffer[twentyfour + 2] + (buffer[twentyfour + 3] << eight);
    out->infoheader.bitPix = buffer[twentyfour + 4] + (buffer[thirty - 1] << eight);
    out->infoheader.biCompression = buffer[thirty] + (buffer[thirty + 1] << eight)
        + (buffer[thirty + 2] << sixteen) + (buffer[thirty + 3] << twentyfour);
    out->infoheader.biSizeImage = buffer[thirty + 4] + (buffer[thirty + five] << eight)
        + (buffer[thirty + six] << sixteen) + (buffer[thirty + seven] << twentyfour);
    out->infoheader.biXPelsPerMeter = buffer[thirty + eight] + (buffer[thirty + nine] << eight)
        + (buffer[forty] << sixteen) + (buffer[forty + 1] << twentyfour);
    out->infoheader.biYPelsPerMeter = buffer[forty + 2] + (buffer[forty + 3] << eight)
        + (buffer[forty + 4] << sixteen) + (buffer[forty + five] << twentyfour);
    out->infoheader.biClrUsed = buffer[fifty - 4] + (buffer[fifty - 3] << eight)
        + (buffer[fifty - 2] << sixteen) + (buffer[fifty - 1] << twentyfour);
    out->infoheader.biClrImportant = buffer[fifty] + (buffer[fifty + 1] << eight)
        + (buffer[fifty + 2] << sixteen) + (buffer[fifty + 3] << twentyfour);
    out->bitmap = (Pixel**) malloc(out->infoheader.height * sizeof(Pixel*));
    for (i = 0; i < out->infoheader.height; i++) {
        out->bitmap[i] = (Pixel*) malloc(out->infoheader.width * sizeof(Pixel));
    }
    paddingBytes = (4 - (3 * out->infoheader.width) % 4) % 4;
    k = 0;
    i = (int) out->fileheader.imageDataOffset;
    while (k != out->infoheader.height) {
        for (j = 0; j < out->infoheader.width; j++) {
            out->bitmap[out->infoheader.height - k - 1][j].b = buffer[i + 3 * j];
            out->bitmap[out->infoheader.height - k - 1][j].g = buffer[i + 3 * j + 1];
            out->bitmap[out->infoheader.height - k - 1][j].r = buffer[i + 3 * j + 2];
        }
        i += (out->infoheader.width) * 3 + paddingBytes;
        k += 1;
    }
    free(buffer);
    return out;
}

void saveImage(Image* img, char* path) {
    FILE *f = fopen(path, "wb");
    fwrite(&img->fileheader.fileMarker1, 1, sizeof(img->fileheader.fileMarker1), f);
    fwrite(&img->fileheader.fileMarker2, 1, sizeof(img->fileheader.fileMarker2), f);
    fwrite(&img->fileheader.bfSize, 1, sizeof(img->fileheader.bfSize), f);
    fwrite(&img->fileheader.unused1, 1, sizeof(img->fileheader.unused1), f);
    fwrite(&img->fileheader.unused2, 1, sizeof(img->fileheader.unused2), f);
    fwrite(&img->fileheader.imageDataOffset, 1, sizeof(img->fileheader.imageDataOffset), f);

    fwrite(&img->infoheader.biSize, 1, sizeof(img->infoheader.biSize), f);
    fwrite(&img->infoheader.width, 1, sizeof(img->infoheader.width), f);
    fwrite(&img->infoheader.height, 1, sizeof(img->infoheader.height), f);
    fwrite(&img->infoheader.planes, 1, sizeof(img->infoheader.planes), f);
    fwrite(&img->infoheader.bitPix, 1, sizeof(img->infoheader.bitPix), f);
    fwrite(&img->infoheader.biCompression, 1, sizeof(img->infoheader.biCompression), f);
    fwrite(&img->infoheader.biSizeImage, 1, sizeof(img->infoheader.biSizeImage), f);
    fwrite(&img->infoheader.biXPelsPerMeter, 1, sizeof(img->infoheader.biXPelsPerMeter), f);
    fwrite(&img->infoheader.biYPelsPerMeter, 1, sizeof(img->infoheader.biYPelsPerMeter), f);
    fwrite(&img->infoheader.biClrUsed, 1, sizeof(img->infoheader.biClrUsed), f);
    fwrite(&img->infoheader.biClrImportant, 1, sizeof(img->infoheader.biClrImportant), f);
    int paddingBytes = (4 - (3 * img->infoheader.width) % 4) % 4;
    int i = 0, j = 0, a = 0;
    unsigned char blank = 0;
    for (i = 0; i < img->infoheader.height; i++) {
        for (j = 0; j < img->infoheader.width; j++) {
            fwrite(&img->bitmap[img->infoheader.height - i - 1][j].b,
             1, sizeof(img->bitmap[img->infoheader.height - i - 1][j].b), f);
            fwrite(&img->bitmap[img->infoheader.height - i - 1][j].g,
             1, sizeof(img->bitmap[img->infoheader.height - i - 1][j].g), f);
            fwrite(&img->bitmap[img->infoheader.height - i - 1][j].r,
             1, sizeof(img->bitmap[img->infoheader.height - i - 1][j].r), f);
        }
        for (j = 0; j < paddingBytes; j++) {
            fwrite(&blank, sizeof(unsigned char), 1, f);
        }
    }
    fclose(f);
}
