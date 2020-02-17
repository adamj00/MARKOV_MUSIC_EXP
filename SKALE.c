#include <stdlib.h>
#include <stdio.h>
#include "STRUKTURY.h"
#include <time.h>


int znajdz_dzwiek(char *dzwiek);
void pokaz_dzwiek (int dzwiek);

int *prawd_interwalu;
int **macierz_interwalow;

Skala stworz_skale (Ustawienia ust) {
    Skala skala;
    skala.dlugosc = ILE_DZWIEKOW;


        if (ust.skala == 0){
            skala.dlugosc_cyklu = 7;
            int cykl [] = {2,1,2,2,1,2,2};
            skala.cykl = malloc (skala.dlugosc_cyklu * sizeof (int));
            for (int i=0;i<skala.dlugosc_cyklu;i++)
                skala.cykl[i] = cykl[i];
        }

        if (ust.skala == 1){
            skala.dlugosc_cyklu = 7;
            int cykl[7] = {2,2,1,2,2,2,1};
            skala.cykl = malloc (skala.dlugosc_cyklu * sizeof (int));
            for (int i=0; i<skala.dlugosc_cyklu; i++)
                skala.cykl[i] = cykl[i];
        }

        if (ust.skala == 2){
            skala.cykl = ust.cykl;
            skala.dlugosc_cyklu = ust.dlugosc_cyklu;
        }



    int pierwszy = znajdz_dzwiek(ust.dzwiek_startowy);

    skala.dzwieki = malloc (skala.dlugosc * sizeof (int));
    for (int i=0;i<skala.dlugosc; i++){
        skala.dzwieki[i] = 0;
    }

    int i = pierwszy;
    int j = 0;
    while (i + skala.cykl[j] < ILE_DZWIEKOW){
        i += skala.cykl[j];
        skala.dzwieki[i] = 1;
        j++;
        if (j == skala.dlugosc_cyklu)
            j=0;
    }


    i = pierwszy;
    j = skala.dlugosc_cyklu - 1;
    skala.dzwieki[pierwszy] = 1;
    while (i - skala.cykl[j] >= 0){
        i -= skala.cykl[j];
        skala.dzwieki [i] = 1;
        j--;
        if (j<0)
            j = skala.dlugosc_cyklu -1;

    }

    return skala;
}

void analizuj_interwaly (Utwor utwor){
    int *interwaly = malloc (utwor.dlugosc * sizeof (int));

    prawd_interwalu = malloc ((ILE_DZWIEKOW*2 -1) * sizeof (int));
    for (int i=0;i<ILE_DZWIEKOW*2 -1;i++)
        prawd_interwalu[i] = 0;

    int odleglosc;
    int poz1 = -1, poz2;
    int idx=0;
    while (poz1 == -1){
        poz1 = znajdz_dzwiek(utwor.dzwieki[idx]);
        idx ++;
    }

    int itv_idx = 0;

    for (int i=idx; i<utwor.dlugosc; i++){
        poz2 = znajdz_dzwiek(utwor.dzwieki[i]);
        if (poz1 == -1 || poz2 == -1)
            continue;

        odleglosc = poz2 - poz1;
        prawd_interwalu [odleglosc + ILE_DZWIEKOW -1] ++;
        interwaly [itv_idx] = odleglosc + ILE_DZWIEKOW -1;
        itv_idx ++;
        poz1 = poz2;
    }

    macierz_interwalow = malloc ((ILE_DZWIEKOW*2 -1) * sizeof (int*));


    for (int i=0;i<ILE_DZWIEKOW*2 -1; i++){
        macierz_interwalow[i] = malloc ((ILE_DZWIEKOW*2 - 1)* sizeof (int));
        for (int j=0; j<ILE_DZWIEKOW*2 - 1; j++)
            macierz_interwalow[i][j] = 0;
    }
    for (int i=1; i<itv_idx; i++){
        macierz_interwalow[interwaly[i-1]] [interwaly[i]] ++;
    }
    free (interwaly);

}


int wylosuj_interwal (int *prawdopodobienstwa, int losowa){
    int suma =0;
    for (int i=0; i< ILE_DZWIEKOW*2 -1; i++)
        suma += prawdopodobienstwa[i];
    if (!suma){
        printf ("prawdopodobienstwo kazdego przejscia wynosi 0\n");
        return -1;
    }
    int *kulki = malloc (suma * sizeof (int));
    int idx=0;
    for (int i=0;i<ILE_DZWIEKOW*2 -1;i++){
        for (int j=0; j<prawdopodobienstwa[i]; j++){
            kulki[idx + j] = i;
        }
        idx += prawdopodobienstwa [i];
    }
    int wynik = kulki [losowa%suma];
    free (kulki);
    return wynik;
}

Markov generuj_lancuch_SKALE (int dlugosc, Skala skala, int zarodek){
    srand (zarodek);

    Markov lancuch;
    lancuch.dlugosc = dlugosc;
    lancuch.lancuch = malloc (dlugosc * sizeof (int));

    lancuch.lancuch [0] = znajdz_dzwiek("C");  // zmienic !!
    int interwal;
    int pop_interwal = wylosuj_interwal(prawd_interwalu,rand());
    int loop;
    for (int i=1;i<dlugosc;i++){
        loop = 0;
        do{
            interwal = wylosuj_interwal(macierz_interwalow[pop_interwal],rand());
            loop++;
        }while (loop <100 && ( lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1) > ILE_DZWIEKOW -12 || lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1) < 0 || skala.dzwieki[lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1)] == 0));
        if (loop == 100){
            //printf ("zapetlenie!\n");
                    loop = 0;
            do{
                interwal = wylosuj_interwal(prawd_interwalu,rand());
                loop++;
            }while (loop <100 && ( lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1) > ILE_DZWIEKOW -12 || lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1) < 0 || skala.dzwieki[lancuch.lancuch[i-1] + interwal - (ILE_DZWIEKOW-1)] == 0));
        if (loop == 100){
            exit (1);
        }
        }

        pop_interwal = interwal;
        interwal -= (ILE_DZWIEKOW -1);
       // printf ("%d ",interwal);
      //  if (lancuch.lancuch[i-1] + interwal >= ILE_DZWIEKOW-11 || lancuch.lancuch[i-1] + interwal < 0)
        //    interwal *= -1;
        lancuch.lancuch[i] = lancuch.lancuch[i-1] + interwal;

    }
    return lancuch;
}
