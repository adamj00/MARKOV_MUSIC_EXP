#ifndef SKALE_H_INCLUDED
#define SKALE_H_INCLUDED

Skala stworz_skale ();
void analizuj_interwaly (Utwor utwor);
int wylosuj_interwal (int *prawdopodobienstwa, int losowa);
Markov generuj_lancuch_SKALE (int dlugosc, Skala skala, int zarodek);

#endif // SKALE_H_INCLUDED
