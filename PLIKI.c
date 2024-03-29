#include <stdio.h>
#include <stdlib.h>
#include "STRUKTURY.h"
#include <string.h>


#define skip fscanf(plik,"%s",trash)


int czy_dzwiek(char *napis, Ustawienia ust);

int znajdz_dzwiek (char *dzwiek, Ustawienia ust){
    if (dzwiek == NULL)
        return -1;
    if (!czy_dzwiek(dzwiek, ust)){
        return -1;
    }
    for (int i=0;i<ILE_DZWIEKOW;i++){
        if (!strcmp(ust.lista_dzw[i],dzwiek))
            return i;
    }

    char *glowa = malloc (20*sizeof (char));
    glowa = "abcdefgABCDEFG,'^";
    int pozycja = strspn(dzwiek,glowa);
    char *nowy_dzwiek  = malloc ( (2+pozycja) * sizeof (char));
    nowy_dzwiek [pozycja] = '\0';
    for (int i=0;i<pozycja;i++){
        nowy_dzwiek [i] = dzwiek [i];
    }
    free (nowy_dzwiek);
    return znajdz_dzwiek(nowy_dzwiek,ust);
}

Utwor czytaj_z_pliku (char *nazwa_pliku){
    FILE *plik = fopen (nazwa_pliku,"rt");
    if (!plik) {
        printf("BLAD\n");
        exit(1);
    }
    int ile_pop=0;
    char trash [2048];
    while (fscanf (plik,"%s",trash) != EOF){
            ile_pop++;
    }
    Utwor utwor;
    fclose (plik);
    plik = fopen (nazwa_pliku, "rt");
    char *dzwiek;
    utwor.dzwieki = malloc(ile_pop*sizeof(char*));
    int i=0;
    while (i<ile_pop){
        dzwiek = malloc (2048*sizeof (char));
        fscanf (plik,"%s",dzwiek);
            utwor.dzwieki[i] = dzwiek;
            i++;
        }

        utwor.dlugosc = ile_pop;

    fclose(plik);

    return utwor;
}

Ustawienia wczytaj_ustawienia () {
    Ustawienia ust;
    int wybor;
    ust.lista_dzw = malloc (ILE_DZWIEKOW * sizeof (char *));

    FILE *lista = fopen ("config\\LISTA_DZWIEKOW.txt","rt");
    if (!lista){
        printf("\nPodczas otwierania pliku LISTA_DZWIEKOW.txt wystapil blad\n");
        exit (1);
    }


    for (int i=0; i<ILE_DZWIEKOW; i++){
        ust.lista_dzw[i] = malloc (5* sizeof (char));
        fscanf (lista,"%s",ust.lista_dzw[i]);
    }

    fclose(lista);


    printf ("Wybierz:\n[0] Ustawienia z pliku\n[1] Ustawienia reczne\n");
    scanf("%d",&wybor);
    if (wybor){
        printf ("Podaj dlugosc utworu: ");
        scanf ("%d", &ust.dlugosc_utworu);
        printf ("Podaj dlugosc pojedynczego lancucha: ");
        scanf ("%d",&ust.dlugosc_lanc);
        printf ("Podaj nazwe pliku z melodia: ");
        ust.nazwa_melodia = malloc (256 * sizeof (char));
        scanf ("%s",ust.nazwa_melodia);
        printf ("Podaj nazwe pliku z rytmem: ");
        ust.nazwa_rytm = malloc (256 * sizeof (char));
        scanf ("%s",ust.nazwa_rytm);
        printf ("Wybierz algorytm:\n[0] Algorytm losowania na podstawie dzwiekow\n[1] Algorytm losowania na podstawie interwalow (+ wybor skali)\n");
        scanf("%d", &ust.algorytm);
        if (ust.algorytm){
            printf ("Wybierz typ skali:\n[0] Molowa\n[1] Durowa\n[2] Niestandardowa\n");
            scanf ("%d",&ust.skala);
            if (ust.skala == 2){
                printf ("Podaj dlugosc cyklu: ");
                scanf ("%d",&ust.dlugosc_cyklu);
                printf ("Podaj %d interwalow: ",ust.dlugosc_cyklu);
                ust.cykl = malloc (ust.dlugosc_cyklu * sizeof (int));
                for (int i=0; i<ust.dlugosc_cyklu; i++)
                    scanf ("%d",&ust.cykl[i]);
            }
            printf ("Podaj dzwiek startowy: ");
            ust.dzwiek_startowy = malloc (36* sizeof (char));
            scanf ("%s",ust.dzwiek_startowy);
        }
        printf ("Podaj metrum: ");
        ust.metrum = malloc (16* sizeof (char));
        scanf ("%s", ust.metrum);
        printf ("Podaj tempo: ");
        ust.tempo = malloc (16* sizeof (char));
        scanf ("%s", ust.tempo);
    }
    else {
        FILE *plik = fopen ("config\\ustawienia.txt", "rt");
        if (!plik){
            printf ("Podczas otwierania pliku z ustawieniami wystapil blad.\n");
            exit(1);
        }

        char *trash = malloc (256 * sizeof (char));
        skip;
        fscanf (plik,"%d", &ust.dlugosc_utworu);
        skip;
        fscanf (plik, "%d", &ust.dlugosc_lanc);
        skip;
        ust.nazwa_melodia = malloc (256 * sizeof (char));
        fscanf (plik,"%s",ust.nazwa_melodia);
        skip;
        ust.nazwa_rytm = malloc (256 * sizeof (char));
        fscanf (plik,"%s",ust.nazwa_rytm);
        skip;
        fscanf (plik, "%d", &ust.algorytm);
        skip;
        ust.metrum = malloc (36 * sizeof (char));
        fscanf (plik, "%s", ust.metrum);
        skip;
        ust.tempo = malloc (36 * sizeof (char));
        fscanf (plik, "%s", ust.tempo);
        skip;
        skip;
        if (ust.algorytm){
            fscanf(plik,"%d",&ust.skala);
            skip;
            ust.dzwiek_startowy = malloc (36 * sizeof (char));
            fscanf (plik,"%s",ust.dzwiek_startowy);
            skip;
            skip;
            if (ust.skala == 2){
                fscanf (plik,"%d",&ust.dlugosc_cyklu);
                skip;
                ust.cykl = malloc (ust.dlugosc_cyklu * sizeof (int));
                for (int i=0; i<ust.dlugosc_cyklu; i++)
                    fscanf (plik, "%d", &ust.cykl[i]);
            }
        }
        fclose (plik);
        free (trash);
    }

    return ust;
}

