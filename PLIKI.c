#include <stdio.h>
#include <stdlib.h>
#include "STRUKTURY.h"
#include <string.h>
#include "RYTM.h"
char *lista_dzwiekow [ILE_DZWIEKOW];

void lista_z_pliku (){
    FILE *plik = fopen ("config\\LISTA_DZWIEKOW.txt","rt");

    if (!plik){
        printf("\nPodczas otwierania pliku LISTA_DZWIEKOW.txt wystapil blad\n");
        exit (1);
    }

    for (int i=0; i<ILE_DZWIEKOW; i++){
        lista_dzwiekow[i] = malloc (5* sizeof (char));
        fscanf (plik,"%s",lista_dzwiekow[i]);
    }

    fclose(plik);
}

int znajdz_dzwiek (char *dzwiek){
    if (dzwiek == NULL)
        return -1;
    if (!czy_dzwiek(dzwiek)){
        printf ("%s ",dzwiek);
        return -1;
    }
    for (int i=0;i<ILE_DZWIEKOW;i++){
        if (!strcmp(lista_dzwiekow[i],dzwiek))
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
    return znajdz_dzwiek(nowy_dzwiek);
}

Utwor czytaj_z_pliku (char *nazwa_pliku){
    FILE *plik = fopen (nazwa_pliku,"rt");
    if (!plik) {
        printf("BLAD\n");
        exit(1);
    }
    int ile_pop=0;
    //char *trash = malloc (5056*sizeof (char));
    char trash [2048];
    while (fscanf (plik,"%s",trash) != EOF){
        //if (znajdz_dzwiek(trash) != -1)
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
            //if (znajdz_dzwiek(dzwiek) != -1){
            utwor.dzwieki[i] = dzwiek;
            i++;
           // }
        }

        utwor.dlugosc = ile_pop;

   // free (trash);
    fclose(plik);
    printf ("dlugosc utworu: %d\n",utwor.dlugosc);
    return utwor;
}


