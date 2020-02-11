#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PLIKI.h"

#include "STRUKTURY.h"

int czy_dzwiek (char *napis){
    //WARUNEK I
    for (int i=0;i<ILE_DZWIEKOW;i++){
        if (!strcmp(napis,lista_dzwiekow[i]))
            return 1;
    }

    int i;
    for (i=0;i<ILE_DZWIEKOW;i++){
        if (strstr(napis,lista_dzwiekow[i]) != NULL)
            break;
        if (i == ILE_DZWIEKOW-1)
            return 0;
    }

    //WARUNEK II i III
    char dozwolone [31] = "^,/123456789abcdefghABCDEFGH'z";
    if (strspn(napis,dozwolone) < strlen(napis))
        return 0;
    return 1;

}

Rytm analizuj_rytm(Utwor utwor){
    Rytm rytm;
    rytm.wartosci_rytmiczne = malloc(utwor.dlugosc * sizeof(char*));

    int ile = 0;

    for (int i=0;i<utwor.dlugosc;i++){
        if (czy_dzwiek(utwor.dzwieki[i])){
            ile ++;
            printf ("%s ",utwor.dzwieki[i]);
        }

    }

printf ("\nile nie dzwiekow:%d\n",utwor.dlugosc-ile);
    return rytm;
}
