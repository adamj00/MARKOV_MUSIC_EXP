#ifndef MARKOV_H_INCLUDED
#define MARKOV_H_INCLUDED

void analizuj_rozklad (Utwor utwor, double **rozklad);
Markov generuj_lancuch (int dlugosc,double **macierz,int zarodek);
Utwor sklej_utwor (Markov *lancuchy,  int ile_lancuchow);
int wylosuj (double *prawdopodobienstwa, int zakres, int losowa);
double akceptacja (int x, int y);
void printLancuch (Markov lancuch);
void zapisz_utwor (Utwor utwor);
#endif // MARKOV_H_INCLUDED