#ifndef DICSOSEG_H_INCLUDED
#define DICSOSEG_H_INCLUDED

int dicsoseg_ir(char* nev, int nyeremeny,unsigned ido, int segitsegek);
int dicsoseg_olvas();

typedef struct Dicsoseg{
int helyezes; char nev[50]; int nyeremeny; unsigned ido; int segitsegek;
}Dicsoseg;

#endif // DICSOSEG_H_INCLUDED
