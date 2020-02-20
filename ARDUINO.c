#include <stdio.h>
#include <stdlib.h>
#include "STRUKTURY.h"
#include "ARDUINO.h"

void rozwin_program (Markov lancuchy[], int ile){
    FILE *plik = fopen ("output\\FLOPPY\\FLOPPY.ino","wt");
    if (!plik){
        printf ("Podczas otwierania pliku FLOPPY.ino wystapil blad.\n");
        exit(1);
    }
    naglowek(plik);
    int ile_dzwiekow = lista_dzwiekow_arduino(lancuchy,ile,plik);
    fprintf(plik,"void loop(){\nfor (int i=0;i < %d; i++){\nplay (freq[dzwieki[i]+17] , 250, i%%2);\ndelay (50);\n}\n  delay (999999);\n}\n",ile_dzwiekow);
    funkcje (plik);
    fclose (plik);
}

int lista_dzwiekow_arduino (Markov lancuchy[], int ile, FILE *plik){
    int ile_dzwiekow=0;
    fprintf (plik, "char dzwieki[] ={");
    for (int i=0;i<ile-1;i++){
        for (int j=0;j<lancuchy[i].dlugosc;j++){
            fprintf(plik, "%d,",lancuchy[i].lancuch[j]);
            ile_dzwiekow++;
        }
    }
    for (int i=0; i<lancuchy[ile-1].dlugosc-1;i ++){
        fprintf(plik, "%d,",lancuchy[ile-1].lancuch[i]);
        ile_dzwiekow++;
    }
    fprintf (plik,"%d};\n",lancuchy[ile-1].lancuch[lancuchy[ile-1].dlugosc-1]);
    ile_dzwiekow++;
    return ile_dzwiekow;
}

void naglowek (FILE *plik){
    fprintf(plik, "void setup() {\npinMode(2,OUTPUT);\npinMode(3,OUTPUT);\n}\n");
    fprintf (plik, "int freq[] = {16,17,18,19,20,21,23,24,26,27,29,31,32,34,36,39,41,43,46,49,52,55,58,62,65,69,73,78,82,87,92,98,104,110,116,123,130,139,147,155,165,174,185,196,207,220,233,247,261,277,293,311,329,349,369,392,415,440};\n");
}
void funkcje(FILE *plik){
    FILE *szablon = fopen ("config\\ARDUINO.txt","rt");
    if (!szablon){
        printf ("Podczas otwierania pliku ARDUINO.txt wystapil blad.\n");
        exit (1);
    }
    char wiersz[2048];
    while (fgets(wiersz,2048,szablon) != NULL){
        fprintf(plik,"%s\n",wiersz);
    }
    fclose (szablon);
}
