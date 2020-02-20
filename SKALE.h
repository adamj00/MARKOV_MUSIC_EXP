#ifndef SKALE_H_INCLUDED
#define SKALE_H_INCLUDED

Skala stworz_skale (Ustawienia ust);
void analizuj_interwaly (Utwor utwor, Ustawienia ust);
int wylosuj_interwal (int *prawdopodobienstwa, int losowa);
Markov generuj_lancuch_SKALE (int dlugosc, Skala skala, int zarodek, Ustawienia ust);

#endif // SKALE_H_INCLUDED
