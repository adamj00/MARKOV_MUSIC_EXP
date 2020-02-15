#include "STRUKTURY.h"
#include "PLIKI.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dev.h"
#define dlugosc_lancucha 10



double rozklad_stacjonarny [ILE_DZWIEKOW];

void rozklad_z_pliku(){
    FILE *plik = fopen ("config\\PORZADANY_ROZKLAD.txt","rt");

    if (!plik){
        printf("\nPodczas otwierania pliku PORZADANY_ROZKLAD.txt wystapil blad\n");
        printf("\nPodczas otwierania pliku PORZADANY_ROZKLAD.txt wystapil blad\n");
        exit (1);
    }

    for (int i=0; i<ILE_DZWIEKOW; i++){
        fscanf (plik,"%lf",&rozklad_stacjonarny[i]);
    }

    fclose(plik);

}


void analizuj_rozklad (Utwor utwor, double **rozklad){
    rozklad_z_pliku();
    lista_z_pliku();
    for (int i=0;i<ILE_DZWIEKOW;i++){
        for (int j=0;j<ILE_DZWIEKOW;j++)
            rozklad [i][j] = 0;
    }

    int poz1,poz2;
    for (int i=0; i<utwor.dlugosc-1;i++){
            poz1 = znajdz_dzwiek(utwor.dzwieki[i]);
            poz2 = znajdz_dzwiek(utwor.dzwieki[i+1]);
            if (poz1 == -1 || poz2 == -1)   continue;
            rozklad [poz1][poz2] ++;

    }
    int suma_wiersza;
    for (int i=0;i<ILE_DZWIEKOW;i++){
        suma_wiersza =0;
        for (int j=0;j<ILE_DZWIEKOW;j++)
            suma_wiersza += rozklad[i][j];
        for (int j=0;j<ILE_DZWIEKOW;j++){
            if (suma_wiersza)
                rozklad[i][j] /= suma_wiersza;
            }
    }

    printMacierz(rozklad);
}

double akceptacja (int x, int y){
    double iloraz = rozklad_stacjonarny[y]/rozklad_stacjonarny[x];
    if (iloraz<1)   return iloraz;
    return 1;
}

int wylosuj (double *prawdopodobienstwa, int zakres, int losowa){

//dodac dynamiczne alkowanie pamieci

    int kulki [1000];
    int poz_kul = 0;
    for (int i=0;i<zakres;i++){
        for (int j=0;j<prawdopodobienstwa[i]*1000;j++){
            kulki [poz_kul + j] = i;
        }
        poz_kul += prawdopodobienstwa[i]*1000;
    }

    if (!poz_kul){
        //printf ("chuj!\n");
        return wylosuj(rozklad_stacjonarny,ILE_DZWIEKOW,losowa);
    }
  //  for (int i= poz_kul; i<999;i++)
     //   kulki[i] = zakres/3;

    int wynik = kulki [losowa%poz_kul];
    return wynik%zakres;
}


Markov generuj_lancuch (int dlugosc,double **macierz, int zarodek){

    srand(zarodek);

    Markov lancuch;
    if (!dlugosc)   exit(1);
    lancuch.dlugosc = dlugosc;
    lancuch.lancuch = malloc (lancuch.dlugosc* sizeof (int));

    lancuch.lancuch[0] = wylosuj(rozklad_stacjonarny,ILE_DZWIEKOW,rand());
    int kandydat,prawd_akc;
    for (int i=1;i<dlugosc;i++){
        do{
            kandydat = wylosuj (macierz[lancuch.lancuch[i-1]],ILE_DZWIEKOW,rand());
            prawd_akc = akceptacja(lancuch.lancuch[i-1],kandydat)*1000;
        }while(rand()%1000 > prawd_akc);
        lancuch.lancuch[i] = kandydat;
    }
    return lancuch;
}

Utwor sklej_utwor (Markov *lancuchy,  int ile_lancuchow){
    Utwor utwor;
    utwor.dlugosc = ile_lancuchow * dlugosc_lancucha;

    utwor.dzwieki = malloc (utwor.dlugosc * sizeof (char *));

    int idx;
    for (int i=0;i<ile_lancuchow;i++){
        for (int j=0;j<lancuchy[i].dlugosc;j++){
            idx = i*dlugosc_lancucha+j;
            utwor.dzwieki[idx] = lista_dzwiekow[lancuchy[i].lancuch[j]];
        }
    }


    return utwor;
}

void zapisz_utwor (Utwor utwor){
    FILE *plik = fopen ("output\\rezultat.abc","wt");
    if (!plik){
        printf("BLAD");
        exit(1);
    }

    char metro [100];
    char tempo [100];
    printf ("Podaj metro: ");
    scanf ("%s",metro);
    printf ("Podaj tempo: ");
    scanf ("%s",tempo);
    fprintf(plik,"X: 1\nT: melodia losowa\nM: %s\nQ: %s\nK: C maj\n",metro,tempo);
    for (int i=0;i<utwor.dlugosc;i++){
        fprintf(plik,"%s\n",utwor.dzwieki[i]);
    }
    printf("\nZAPISANO.\n");
    fclose(plik);

}
