#include <stdio.h>
#include <stdlib.h>
#include "PLIKI.h"
#include "SORT.h"
#include "STRUKTURY.h"
#include "MARKOV.h"
#include "RYTM.h"
#include <time.h>
#include  "SKALE.h"
#include "ARDUINO.h"
int main()
{

    Ustawienia ust = wczytaj_ustawienia();

    double **rozklad = malloc (ILE_DZWIEKOW * sizeof (double *));
    for (int i=0;i<ILE_DZWIEKOW;i++){
        rozklad[i] = malloc (ILE_DZWIEKOW * sizeof (double));
    }


    Utwor zrodlo = czytaj_z_pliku(ust.nazwa_melodia);


    Skala skala;

    if (!ust.algorytm)
        analizuj_rozklad(zrodlo, rozklad,ust);

    else {
        analizuj_interwaly(zrodlo, ust);
        skala = stworz_skale(ust);
    }
    Markov lancuchy[ust.dlugosc_utworu/ust.dlugosc_lanc];

    time_t tt;
    int zarodek = time(&tt);
    srand (zarodek);

    for (int i=0;i<ust.dlugosc_utworu/ust.dlugosc_lanc;i++){
         zarodek = rand();
         if (!ust.algorytm)
            lancuchy[i] = generuj_lancuch(ust.dlugosc_lanc,rozklad,zarodek);
         else{
            lancuchy[i] = generuj_lancuch_SKALE(ust.dlugosc_lanc,skala,zarodek, ust);
         }
    }

    sortuj(lancuchy,ust.dlugosc_utworu/ust.dlugosc_lanc);

    rozwin_program(lancuchy,ust.dlugosc_utworu/ust.dlugosc_lanc);

    Utwor rezultat = sklej_utwor(lancuchy,ust.dlugosc_utworu/ust.dlugosc_lanc,ust);

    Utwor do_rytmu = czytaj_z_pliku(ust.nazwa_rytm);

    Rytm rytm = analizuj_rytm(do_rytmu, ust);

    nadaj_rytm(&rezultat,rytm);

    zapisz_utwor(rezultat, ust);

    return 0;
}
