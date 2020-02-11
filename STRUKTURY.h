#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#define ILE_DZWIEKOW 48

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

#endif // STRUKTURY_H_INCLUDED
