#ifndef MARKOV_H_INCLUDED
#define MARKOV_H_INCLUDED

void analizuj_rozklad (Utwor utwor, double **rozklad, Ustawienia ust);
Markov generuj_lancuch (int dlugosc,double **macierz,int zarodek);
Utwor sklej_utwor (Markov *lancuchy,  int ile_lancuchow, Ustawienia ust);
int wylosuj (double *prawdopodobienstwa, int zakres, int losowa);
double akceptacja (int x, int y);
void printLancuch (Markov lancuch);
void zapisz_utwor (Utwor utwor, Ustawienia ust);
#endif // MARKOV_H_INCLUDED
