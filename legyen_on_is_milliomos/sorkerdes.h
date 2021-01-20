#ifndef SORKERDES_H_INCLUDED
#define SORKERDES_H_INCLUDED

typedef struct Sorkerdes{
char kerdess[200];char a[100]; char b[100]; char c[100]; char d[100]; char valasz[5]; char kategoria[40]; struct Sorkerdes* kov;
}Sorkerdes;

typedef struct Ellenfel{
    char nev[20]; int ido; char valasz[4];
}Ellenfel;

int sorkerdes();
bool jovalasz(char *valasz, char *vizsgal);

#endif // SORKERDES_H_INCLUDED
