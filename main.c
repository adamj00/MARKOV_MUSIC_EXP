#include <stdio.h>
#include <stdlib.h>
#include "PLIKI.h"
#include "STRUKTURY.h"
#include "MARKOV.h"
#include "RYTM.h"
#define PLIK "input\\BACH.abc"
#define dlugosc_lancucha 100
#include <time.h>
int main()
{
    lista_z_pliku();
    int dlugosc;
    printf("DLUGOSC:\n");
    scanf("%d",&dlugosc);

    double **rozklad = malloc (ILE_DZWIEKOW * sizeof (double *));
    for (int i=0;i<ILE_DZWIEKOW;i++){
        rozklad[i] = malloc (ILE_DZWIEKOW * sizeof (double));
    }

    Utwor zrodlo = czytaj_z_pliku(PLIK);

    analizuj_rozklad(zrodlo, rozklad);

    Markov lancuchy[dlugosc/dlugosc_lancucha];

    time_t tt;
    int zarodek = time(&tt);
    srand (zarodek);

    for (int i=0;i<dlugosc/dlugosc_lancucha;i++){
         zarodek = rand();
         lancuchy[i] = generuj_lancuch(dlugosc_lancucha,rozklad,zarodek);
    }

    for (int i=0;i<dlugosc/dlugosc_lancucha;i++){
        printf ("lancuch %d:",i);
        printLancuch(lancuchy[i]);
    }

    Utwor rezultat = sklej_utwor(lancuchy,dlugosc/dlugosc_lancucha);

    Utwor do_rytmu = czytaj_z_pliku("input\\rytm.abc");

    Rytm rytm = analizuj_rytm(do_rytmu);

    nadaj_rytm(&rezultat,rytm);

    zapisz_utwor(rezultat);

    return 0;
}
