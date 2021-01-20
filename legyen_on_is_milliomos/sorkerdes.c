#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorkerdes.h"
#include <time.h>
#include <string.h>
#include <ctype.h>

bool jovalasz(char *valasz, char *vizsgal){
    for(int i=0;i<4;i++){
        if(valasz[i]!=vizsgal[i]){
            return false;
        }
    }
    return true;
}

int sorkerdes(){
    srand(time(NULL));
    Sorkerdes* sorkerdes1;
    sorkerdes1= (Sorkerdes*) malloc(sizeof(Sorkerdes));
    if(sorkerdes==NULL){                                    //a fordító szerint sosem lesz igaz, de azért meg kell vizsgálni
        printf("Nem sikerült memóriát foglalni!\n");
        return 1;
    }
    FILE* fps;
    fps=fopen("loimsor.txt","r");
    if(fps==NULL){
        printf("Nem sikerült megnyitni a fájlt!\n");
        return 2;
    }
    //char temps;
    char* elsosor=(char*) malloc(1000*sizeof(char));
    if(elsosor==NULL){
        printf("Nem sikerült memóriát foglalni!\n");
        return 1;
    }
    int sorkerdesszam=0;
    Sorkerdes* mozgo = sorkerdes1;
    fgets(elsosor, 1000, fps);
    free(elsosor);
    while(true){
        int i=0;
        while(fscanf(fps,"%c",&mozgo->kerdess[i]) && mozgo->kerdess[i]!='\t'){i++;}
        mozgo->kerdess[i]='\0';
        i=0;
        while(fscanf(fps,"%c",&mozgo->a[i]) && mozgo->a[i]!='\t'){i++;}
        mozgo->a[i]='\0';
        i=0;
        while(fscanf(fps,"%c",&mozgo->b[i]) && mozgo->b[i]!='\t'){i++;}
        mozgo->b[i]='\0';
        i=0;
        while(fscanf(fps,"%c",&mozgo->c[i]) && mozgo->c[i]!='\t'){i++;}
        mozgo->c[i]='\0';
        i=0;
        while(fscanf(fps,"%c",&mozgo->d[i]) && mozgo->d[i]!='\t'){i++;}
        mozgo->d[i]='\0';
        for(int j=0;j<4;j++){
            fscanf(fps,"%c",&mozgo->valasz[j]);
        }
        mozgo->valasz[4]='\0';
        i=0;
        fscanf(fps, "%s", &mozgo->kategoria);
        sorkerdesszam++;
        if(fgetc(fps)==EOF){
            mozgo->kov = sorkerdes1;
            break;
        }
        mozgo->kov = (Sorkerdes*) malloc(sizeof(Sorkerdes));
        if(mozgo->kov==NULL){
            printf("Nem sikerült memóriát foglalni!\n");
            return 1;
        }
        mozgo=mozgo->kov;
    }
    fclose(fps);
    Sorkerdes* mozgo1= sorkerdes1;
    printf("\n%d sorkérdést sikerült beolvasni.\n\n",sorkerdesszam);
    Ellenfel ellenfel[7];
    strcpy(ellenfel[0].nev,"BOT_Anna");
    strcpy(ellenfel[1].nev,"BOT_Béla");
    strcpy(ellenfel[2].nev,"BOT_Csaba");
    strcpy(ellenfel[3].nev,"BOT_Dóra");
    strcpy(ellenfel[4].nev,"BOT_Eszter");
    strcpy(ellenfel[5].nev,"BOT_Ferenc");
    strcpy(ellenfel[6].nev,"BOT_Gréta");
    for(int i=0;i<7;i++){
        ellenfel[i].ido=rand()%16+10;
        ellenfel[i].valasz[0]=rand()%4+65;
        do{ellenfel[i].valasz[1]=rand()%4+65;}
            while(ellenfel[i].valasz[1]==ellenfel[i].valasz[0]);        //addig generáljuk a következő karaktereket, amíg egyik előzővel sem egyeznek
        do{ellenfel[i].valasz[2]=rand()%4+65;}
            while(ellenfel[i].valasz[2]==ellenfel[i].valasz[0] || ellenfel[i].valasz[2]==ellenfel[i].valasz[1]);
        do{ellenfel[i].valasz[3]=rand()%4+65;}
            while(ellenfel[i].valasz[3]==ellenfel[i].valasz[0] || ellenfel[i].valasz[3]==ellenfel[i].valasz[1] || ellenfel[i].valasz[3]==ellenfel[i].valasz[2]);
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(ellenfel[j].ido>ellenfel[j+1].ido){
                Ellenfel temp=ellenfel[j];              //növekvő sorrendbe rendezzük az ellenfeleket idő szerint
                ellenfel[j]=ellenfel[j+1];
                ellenfel[j+1]=temp;
            }
        }
    }

    char temp_elsonev[20]; //enélkül rosszul működik
    int rand_sorkerdes= rand()%sorkerdesszam;
    for(int j=0;j<rand_sorkerdes;j++){
        mozgo1=mozgo1->kov;
    }
    int eleje=0;
    for(int i=0;i<7;i++){
        if(jovalasz(mozgo1->valasz,ellenfel[i].valasz)){
            Ellenfel temp_ellenfel=ellenfel[i];
            for(int j=i;j>eleje;j--){
                ellenfel[j]=ellenfel[j-1];  //a rossz választ adóakat lejjebb csúsztatjuk,
            }
            ellenfel[eleje]=temp_ellenfel;  //és az első helyekre tesszük a jó választ adóakat
            eleje++;
        }
    }
    printf("SORKÉRDÉS:\n");
    printf("Kategória: %s\n%s\n\nA: %s\nB: %s\nC: %s\nD: %s\n",mozgo1->kategoria,mozgo1->kerdess,mozgo1->a,mozgo1->b,mozgo1->c,mozgo1->d);
    //printf("[%s]\n",mozgo1->valasz);
    unsigned idokezd=time(NULL);
    char sorvalasz[4];
    scanf("%s",&sorvalasz);
    for(int i=0;i<4;i++){
        sorvalasz[i]=toupper(sorvalasz[i]);
    }
    unsigned idoveg=time(NULL);
    int sorido=idoveg-idokezd;
    for(int i=0;i<4;i++){
        if(sorvalasz[i]!=mozgo1->valasz[i]){
            printf("Rossz válasz. A helyes válasz: %c%c%c%c. Sajnos nem kezdheted el a játékot.\n",mozgo1->valasz[0],mozgo1->valasz[1],mozgo1->valasz[2],mozgo1->valasz[3]);
            Sorkerdes* iter = sorkerdes1;
            for(int l=0;l<sorkerdesszam;l++){
                    Sorkerdes *kov = iter->kov;
                    free(iter);
                    iter=kov;
            }
            return 6;
        }
    }

    if(jovalasz(ellenfel[0].valasz,mozgo1->valasz) && ellenfel[0].ido<sorido){
        printf("Egy másik játékos gyorsabb volt nálad, sajnos nem kezdheted el a játékot.\nA sorrend:\n");
        bool kiirtuk;
        for(int i=0;i<7;i++){
            if(i==eleje){ //az eleje azt tárolja, hogy hány jó választ adó ellenfél volt.
                printf("TE:\t\t%s\t%d másodperc\n",sorvalasz,sorido);
                kiirtuk=true;
            }
            printf("%s:\t%c%c%c%c\t%d másodperc\n",ellenfel[i].nev,ellenfel[i].valasz[0],ellenfel[i].valasz[1],ellenfel[i].valasz[2],ellenfel[i].valasz[3],ellenfel[i].ido);
        }
        if(kiirtuk==false){
            printf("TE:\t\t%s\t%d másodperc\n",sorvalasz,sorido);
        }
        Sorkerdes* iter = sorkerdes1;
        for(int i=0;i<sorkerdesszam;i++){
            Sorkerdes *kov = iter->kov;
            free(iter);
            iter=kov;
        }
        return 7;
    }else{
        printf("Gratulálok, te voltál a leggyorsabb jó választ adó, elkezdheted a játékot!\nA sorrend:\n");
        printf("TE:\t\t%s\t%d másodperc\n",sorvalasz,sorido);
        for(int i=0;i<7;i++){
            printf("%s:\t%c%c%c%c\t%d másodperc\n",ellenfel[i].nev,ellenfel[i].valasz[0],ellenfel[i].valasz[1],ellenfel[i].valasz[2],ellenfel[i].valasz[3],ellenfel[i].ido);
        }
    }
    Sorkerdes* iter = sorkerdes1;
    for(int i=0;i<sorkerdesszam;i++){
        Sorkerdes *kov = iter->kov;
        free(iter);
        iter=kov;
    }
    return 0;
}
