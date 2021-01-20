#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#ifdef _WIN32
    #include <windows.h>
#endif
#include <time.h>

typedef struct Jatekos{
    char nev[50]; int nyeremeny; bool segitsegek[3]; unsigned ido;
}Jatekos;

typedef struct Kerdes{
int nehezseg; char kerdess[200]; char a[100]; char b[100]; char c[100]; char d[100]; char valasz; char kategoria[40]; bool volt_e; struct Kerdes* kov;
}Kerdes;

int jatek();
int felszabadit(Kerdes* kerdes, int kerdsszam);
int segitsegszam(bool* segitsegek);
int felszabadit(Kerdes* kerdes, int kerdesszam);

#endif // JATEK_H_INCLUDED
