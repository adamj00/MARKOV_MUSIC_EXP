#include <stdio.h>
#include <stdlib.h>
#include "STRUKTURY.h"
#include "PLIKI.h"
#include "MARKOV.h"
#define ILE_DZWIEKOW 48
void printLancuch (Markov lancuch){
    for (int i=0;i<lancuch.dlugosc;i++)
        printf("%d ",lancuch.lancuch[i]);
    printf ("\n");
}

void printMacierz (double **macierz){
    FILE *plik = fopen ("output\\MACIERZ_PRZEJSC.txt","wt");
    if (!plik)
        exit(1);
    //printf("macierz: \n");
    for (int i=0;i<ILE_DZWIEKOW;i++){
        for (int j=0;j<ILE_DZWIEKOW;j++){
            fprintf (plik,"%lf ",macierz[i][j]);
        }
        fprintf(plik,"\n");
    }
    fclose(plik);
}
