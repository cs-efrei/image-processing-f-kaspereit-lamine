#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"
//TEST1
t_bmp8* bmp8_loadImage(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    t_bmp8 *img = (t_bmp8*)malloc(sizeof(t_bmp8));
    if (!img) {
        printf("Erreur : Allocation mémoire échouée\n");
        fclose(file);
        return NULL;
    }

    fread(img->header, 1, 54, file);
    fread(img->colorTable, 1, 1024, file);

    img->width = *(unsigned int*)&img->header[18];
    img->height = *(unsigned int*)&img->header[22];
    img->colorDepth = *(unsigned short*)&img->header[28];
    img->dataSize = *(unsigned int*)&img->header[34];

    if (img->colorDepth != 8) {
        printf("Erreur : L'image n'est pas en niveaux de gris (8 bits)\n");
        free(img);
        fclose(file);
        return NULL;
    }

    img->data = (unsigned char*)malloc(img->dataSize);
    if (!img->data) {
        printf("Erreur : Allocation mémoire pour les données.\n");
        free(img);
        fclose(file);
        return NULL;
    }

    fread(img->data, 1, img->dataSize, file);
    fclose(file);
    return img;
}

void bmp8_saveImage(const char *filename, t_bmp8 *img) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Erreur : Impossible de créer le fichier %s\n", filename);
        return;
    }

    fwrite(img->header, 1, 54, file);
    fwrite(img->colorTable, 1, 1024, file);
    fwrite(img->data, 1, img->dataSize, file);

    fclose(file);
}

void bmp8_free(t_bmp8 *img) {
    if (img) {
        if (img->data) free(img->data);
        free(img);
    }
}

void bmp8_printInfo(t_bmp8 *img) {
    printf("Image Info:\n");
    printf("Width: %u\n", img->width);
    printf("Height: %u\n", img->height);
    printf("Color Depth: %u\n", img->colorDepth);
    printf("Data Size: %u\n", img->dataSize);
}

void bmp8_negative(t_bmp8 *img) {
    for (unsigned int i = 0; i < img->dataSize; i++) {
        img->data[i] = 255 - img->data[i];
    }
}

void bmp8_brightness(t_bmp8 *img, int value) {
    for (unsigned int i = 0; i < img->dataSize; i++) {
        int pixel = img->data[i] + value;
        if (pixel > 255) pixel = 255;
        if (pixel < 0) pixel = 0;
        img->data[i] = (unsigned char)pixel;
    }
}

void bmp8_threshold(t_bmp8 *img, int threshold) {
    for (unsigned int i = 0; i < img->dataSize; i++) {
        img->data[i] = (img->data[i] >= threshold) ? 255 : 0;
    }
}
