#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "jatek.h"
#include "dicsoseg.h"
#ifdef _WIN32
    #include <windows.h>
#endif


char menu(){
    printf("\n\n1: Új játék\n2: Dicsőséglista megtekintése\n3: Kilépés\n");
    char mit;
    mit=getchar();      //int-el tér vissza, de nekünk most pl. az EOF nem jöhet szóba
    return mit;
}

int main()
{
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif
    printf("Legyen Ön Is Milliomos!\n\n");
    printf("Üdvözöllek a menüben! Mit szeretnél csinálni? Nyomj le egy gombot!");
    bool eloszor=true;
    while(true){
        if(!eloszor)getchar();      //ha nem előszöt vagyunk itt, a legutolsó entert fogja a menüre válasznak venni, ezért azt be kell olvasni,
        else eloszor=false;         //és eldobni
        switch(menu()){
            case '1': if(jatek()==0);break;
            case '2': if(dicsoseg_olvas()==0);break;
            case '3': exit(0); break;
            default: printf("Érvénytelen válasz, írj be valami mást!\n"); break;
        }
    }
    return 0;
}
