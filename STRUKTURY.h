#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#define ILE_DZWIEKOW 49


typedef struct Rytm{
    int dlugosc;
    char **wartosci_rytmiczne;
}Rytm;

typedef struct Utwor{
    int dlugosc;
    char **dzwieki;


}Utwor ;
typedef struct Markov{
    int dlugosc;
    int *lancuch;
}Markov;

typedef struct Skala{
    int *dzwieki;
    int *cykl;
    int dlugosc_cyklu;
    int dlugosc;
}Skala;

typedef struct Ustawienia{
    int dlugosc_utworu;
    int dlugosc_lanc;
    char *nazwa_melodia;
    char *nazwa_rytm;
    char **lista_dzw;
    int algorytm;
    char *metrum;
    char *tempo;
    int skala;
    char *dzwiek_startowy;
    int dlugosc_cyklu;
    int *cykl;

}Ustawienia;

#endif // STRUKTURY_H_INCLUDED
