#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"
//TEST1
int main() {
    t_bmp8 *img = NULL;
    char filename[100];
    int choix;
    int valeur;

    printf("=== PARTIE 1 : Traitement d'image BMP 8 bits (Niveaux de gris) ===\n");

    printf("Entrez le chemin de l'image a charger (.bmp) : ");
    scanf("%s", filename);

    img = bmp8_loadImage(filename);
    if (img == NULL) {
        printf("Erreur lors du chargement de l'image.\n");
        return 1;
    }

    printf("Image chargee avec succes !\n");
    bmp8_printInfo(img);

    do {
        printf("\nQue voulez-vous faire ?\n");
        printf("1. Appliquer filtre negatif\n");
        printf("2. Modifier la luminosite\n");
        printf("3. Appliquer un seuillage (binarisation)\n");
        printf("4. Sauvegarder l'image\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            bmp8_negative(img);
            printf("Filtre negatif applique.\n");
        } else if (choix == 2) {
            printf("Entrez la valeur de luminosite (-255 a 255) : ");
            scanf("%d", &valeur);
            bmp8_brightness(img, valeur);
            printf("Modification de la luminosite terminee.\n");
        } else if (choix == 3) {
            printf("Entrez le seuil (0 a 255) : ");
            scanf("%d", &valeur);
            bmp8_threshold(img, valeur);
            printf("Seuillage applique.\n");
        } else if (choix == 4) {
            char savefile[100];
            printf("Entrez le nom du fichier de sauvegarde (.bmp) : ");
            scanf("%s", savefile);
            bmp8_saveImage(savefile, img);
            printf("Image sauvegardee sous %s.\n", savefile);
        } else if (choix == 5) {
            printf("Fermeture du programme.\n");
        } else {
            printf("Choix invalide.\n");
        }

    } while (choix != 5);

    bmp8_free(img);
    return 0;
