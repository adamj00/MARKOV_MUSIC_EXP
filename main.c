#include <stdio.h>
#include <stdlib.h>
#include "PLIKI.h"
#include "SORT.h"
#include "STRUKTURY.h"
#include "MARKOV.h"
#include "RYTM.h"
#define PLIK "input\\BACH.abc"
#include <time.h>
#include  "SKALE.h"
int main()
{
    lista_z_pliku();

    Ustawienia ust = wczytaj_ustawienia();

    double **rozklad = malloc (ILE_DZWIEKOW * sizeof (double *));
    for (int i=0;i<ILE_DZWIEKOW;i++){
        rozklad[i] = malloc (ILE_DZWIEKOW * sizeof (double));
    }


    Utwor zrodlo = czytaj_z_pliku(ust.nazwa_melodia);


    Skala skala;

    if (!ust.algorytm)
        analizuj_rozklad(zrodlo, rozklad);
    else {
        analizuj_interwaly(zrodlo);
        skala = stworz_skale(ust);
    }

    Markov lancuchy[ust.dlugosc_utworu/dlugosc_lancucha];

    time_t tt;
    int zarodek = time(&tt);
    srand (zarodek);

    for (int i=0;i<ust.dlugosc_utworu/dlugosc_lancucha;i++){
         zarodek = rand();
         if (!ust.algorytm)
            lancuchy[i] = generuj_lancuch(dlugosc_lancucha,rozklad,zarodek);
         else{
            lancuchy[i] = generuj_lancuch_SKALE(dlugosc_lancucha,skala,zarodek);
         }
    }

    sortuj(lancuchy,ust.dlugosc_utworu/dlugosc_lancucha);

    Utwor rezultat = sklej_utwor(lancuchy,ust.dlugosc_utworu/dlugosc_lancucha);

    Utwor do_rytmu = czytaj_z_pliku(ust.nazwa_rytm);

    Rytm rytm = analizuj_rytm(do_rytmu);

    nadaj_rytm(&rezultat,rytm);

    zapisz_utwor(rezultat, ust);

    return 0;
}
