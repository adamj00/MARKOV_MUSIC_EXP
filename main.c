#include <stdio.h>
#include <stdlib.h>
#include "PLIKI.h"
#include "SORT.h"
#include "STRUKTURY.h"
#include "MARKOV.h"
#include "RYTM.h"
#define PLIK "input\\BACH.abc"
#define dlugosc_lancucha 8
#include <time.h>
#include  "SKALE.h"
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

    char nazwa_zrodlo[100];
    char nazwa_rytm[100];

    printf("Podaj nazwe pliku, na podstawie ktorego ma zostac utworzona macierz przejsc: ");
    scanf ("%s",nazwa_zrodlo);
    printf("\nPodaj nazwe pliku z rytmem: ");
    scanf ("%s",nazwa_rytm);

    Utwor zrodlo = czytaj_z_pliku(nazwa_zrodlo);


    int wybor;
    printf ("Wybierz algorytm:\n[0] Algorytm losowania na podstawie dzwiekow\n[1] Algorytm losowania na podstawie interwalow (+ wybor skali)\n");
    scanf ("%d", &wybor);

    Skala skala;

    if (!wybor)
        analizuj_rozklad(zrodlo, rozklad);
    else {
        analizuj_interwaly(zrodlo);
        skala = stworz_skale();
    }
    Markov lancuchy[dlugosc/dlugosc_lancucha];

    time_t tt;
    int zarodek = time(&tt);
    srand (zarodek);

    for (int i=0;i<dlugosc/dlugosc_lancucha;i++){
         zarodek = rand();
         if (!wybor)
            lancuchy[i] = generuj_lancuch(dlugosc_lancucha,rozklad,zarodek);
         else{
            lancuchy[i] = generuj_lancuch_SKALE(dlugosc_lancucha,skala,zarodek);
         }
            for (int j=0; j<lancuchy[i].dlugosc; j++){
                printf ("%d ", lancuchy[i].lancuch[j]);
            }
    }

    sortuj(lancuchy,dlugosc/dlugosc_lancucha);

    Utwor rezultat = sklej_utwor(lancuchy,dlugosc/dlugosc_lancucha);

    Utwor do_rytmu = czytaj_z_pliku(nazwa_rytm);

    Rytm rytm = analizuj_rytm(do_rytmu);

    nadaj_rytm(&rezultat,rytm);

    zapisz_utwor(rezultat);

    return 0;
}
