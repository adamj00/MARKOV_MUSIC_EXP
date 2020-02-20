    #include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "STRUKTURY.h"

int czy_dzwiek (char *napis, Ustawienia ust){
    //WARUNEK I
    for (int i=0;i<ILE_DZWIEKOW;i++){
        if (!strcmp(napis,ust.lista_dzw[i]))
            return 1;
    }

    int i;
    for (i=0;i<ILE_DZWIEKOW;i++){
        if (strstr(napis,ust.lista_dzw[i]) != NULL)
            break;
        if (i == ILE_DZWIEKOW-1)
            return 0;
    }

    //WARUNEK II i III
    char *dozwolone = malloc (31 * sizeof (char));
    dozwolone = "^,/123456789abcdefghABCDEFGH'z";
    if (strspn(napis,dozwolone) < strlen(napis)){
        free (dozwolone);
        return 0;
    }
    free (dozwolone);
    return 1;

}

Rytm analizuj_rytm(Utwor utwor, Ustawienia ust){
    Rytm rytm;

    int ile = 0;

    for (int i=0;i<utwor.dlugosc;i++){
        if (czy_dzwiek(utwor.dzwieki[i],ust))
            ile ++;
    }
    rytm.wartosci_rytmiczne = malloc(ile * sizeof(char*));
    rytm.dlugosc = ile;

    int rytm_poz;
    char *glowa = malloc (25*sizeof (char));
    glowa = "abcdefgABCDEFG,'^";
    int idx=0;
    for (int i=0;i<utwor.dlugosc;i++){
        if (czy_dzwiek(utwor.dzwieki[i],ust)){

            if (strchr(utwor.dzwieki[i],'z') != NULL){
                rytm.wartosci_rytmiczne[idx] = malloc ( (strlen(utwor.dzwieki[i]) + 1) * sizeof (char) );
                strcpy(rytm.wartosci_rytmiczne[idx],utwor.dzwieki[i]);
                idx++;
            }

            else{

            rytm_poz = strspn(utwor.dzwieki[i],glowa);
            rytm.wartosci_rytmiczne[idx] = malloc ( (strlen(utwor.dzwieki[i]) - rytm_poz + 1) * sizeof (char) );
            for (int j=0;j<strlen(utwor.dzwieki[i]) - rytm_poz;j++){
                rytm.wartosci_rytmiczne[idx][j] = utwor.dzwieki[i][j+rytm_poz];
            }
            rytm.wartosci_rytmiczne[idx][strlen(utwor.dzwieki[i]) - rytm_poz] = '\0';
            idx++;
        }
        }
    }
    free (glowa);

    return rytm;
}

void nadaj_rytm (Utwor *utwor, Rytm rytm){
    int j=0;
    int idx,idxr;
    char *po_zlaczeniu;
    for (int i=0;i<utwor->dlugosc;i++){
        if (j == rytm.dlugosc)
            j=0;
        if (rytm.wartosci_rytmiczne[j] != NULL){

            po_zlaczeniu = malloc (36 * sizeof (char));


            if (strchr(rytm.wartosci_rytmiczne[j],'z') != NULL){

                    strcpy(po_zlaczeniu,rytm.wartosci_rytmiczne[j]);
                    utwor->dzwieki[i] = po_zlaczeniu;
            }

            else {
            idx = 0;
            while (utwor->dzwieki[i][idx] != '\0'){
                po_zlaczeniu[idx] = utwor->dzwieki[i][idx];
                idx++;
            }
            idxr = 0;
            while (rytm.wartosci_rytmiczne[j][idxr] != '\0'){
                po_zlaczeniu[idx] = rytm.wartosci_rytmiczne[j][idxr];
                idxr++;
                idx++;
            }
            po_zlaczeniu[idx] = '\0';

            utwor->dzwieki [i] = po_zlaczeniu;
        }
        }
        j++;
    }
}
