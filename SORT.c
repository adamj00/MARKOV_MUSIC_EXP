#include <stdlib.h>
#include "STRUKTURY.h"
#include <stdio.h>

void przejscia_z_pliku (double **przejscia){
    FILE *plik = fopen ("config\\ZLE_DOBRE.txt","rt");
    if (!plik){
        printf ("Blad przy otwieraniu pliku ZLE_DOBRE.txt\n");
        exit (1);
    }

    for (int i=0;i<ILE_DZWIEKOW;i++){
        for (int j=0;j<ILE_DZWIEKOW;j++)
            fscanf(plik,"%lf",&przejscia[i][j]);
    }

}

void zamien(Markov *el1, Markov *el2){
    Markov *temp = el1;
    el1 = el2;
    el2 = temp;
}

int maks (Markov *lancuchy, int poprzednie, int start, int ile, double **przejscia){
    double maks_wart = przejscia [poprzednie] [lancuchy[start].lancuch[0]];
    int wynik = start;
    for (int i=start;i<ile;i++){
         if (maks_wart < przejscia [poprzednie] [lancuchy[i].lancuch[0]]){
             maks_wart = przejscia [poprzednie] [lancuchy[i].lancuch[0]];
             wynik = i;
         }
    }
    return wynik;
}

void sortuj (Markov *lancuchy, int ile){
    double **przejscia = malloc (ILE_DZWIEKOW * sizeof (double *));
    for (int i=0; i<ILE_DZWIEKOW; i++)
        przejscia[i] = malloc (ILE_DZWIEKOW * sizeof (double));

    przejscia_z_pliku(przejscia);
    int najlepszy;
    for (int i=1; i<ile; i++){
        najlepszy = maks (lancuchy, lancuchy[i-1].lancuch[lancuchy[i-1].dlugosc-1], i, ile, przejscia);
        zamien(&lancuchy[i],&lancuchy[najlepszy]);
    }
}
