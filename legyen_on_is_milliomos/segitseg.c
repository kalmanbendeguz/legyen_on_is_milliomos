#include "segitseg.h"
#include <stdio.h>
#include <time.h>

int segitseg(Kerdes* kerdes, char milyen, char* megmaradtak){
    srand(time(NULL));
    if(milyen=='T'){
        int szazalek= rand()%100;
        if(szazalek<80){ //80%-os eséllyel
            printf("\nTelefon: \"Szerintem a %c a jó válasz.\"\n",kerdes->valasz);
        }else{
            char rosszak[3];
            int j=0;
            char abcd[4]={'A','B','C','D'};
            for(int i=0;i<4;i++){
                if(abcd[i]!=(kerdes->valasz)){
                    rosszak[j++]=abcd[i]; //beteszi egy tömbbe a 3 rosszat,
                }
            }
            int rossz=rand()%3; //és azokból ír ki egyet véletlenszerűen.
            printf("\nTelefon: ");
            printf("\"Szerintem a %c a jó válasz.\"\n",rosszak[rossz]);
            }
        }
    else if(milyen=='F'){
        char rosszak[3];
            int j=0;
            char abcd[4]={'A','B','C','D'};
            for(int i=0;i<4;i++){
                if(abcd[i]!=(kerdes->valasz)){
                    rosszak[j++]=abcd[i]; //eltárolja a rosszakat
                }
            }
        int melyiket_nem_vesz_el=rand()%3; //ezek közül generál egyet, amit kiír a jó válasz mellé
        megmaradtak[0]=rosszak[melyiket_nem_vesz_el];
        megmaradtak[1]=kerdes->valasz;
        printf("\nA felezés után megmaradt lehetőségek:\n");
            if(rosszak[melyiket_nem_vesz_el]<kerdes->valasz){
                printf("%c\n",rosszak[melyiket_nem_vesz_el]);   //
                printf("%c\n",kerdes->valasz);                  //
            }else{                                              // hogy a sorrendből ne lehessen rájönni
                printf("%c\n",kerdes->valasz);                  //
                printf("%c\n",rosszak[melyiket_nem_vesz_el]);   //
            }
    }else if(milyen=='K'){
        int aranytemp[3];
        for(int i=0;i<3;i++){                       // közönség-segítség kiszámításának módszere:
            aranytemp[i]=rand()%101;                // először generálok 3 random számot 0 és 100 között
        }                                           //
        for(int i=0;i<2;i++){                       //
            for(int j=0;j<2;j++){                   //
                if(aranytemp[j]>aranytemp[j+1]){    //
                    int temp=aranytemp[j];          // növekvő sorrendbe rendezzük őket
                    aranytemp[j]=aranytemp[j+1];    //
                    aranytemp[j+1]=temp;            //
                }
            }
        }
        int arany[4];
        arany[0]=aranytemp[0];                      // az első százalék: a 0. elem
        arany[1]=aranytemp[1]-aranytemp[0];         // a második százalék 1. elem - 0. elem
        arany[2]=aranytemp[2]-aranytemp[1];         // a harmdaik: 2. elem - 1. elem
        arany[3]=100-aranytemp[2];                  // a negyedik: 100- 2. elem
        int esely= rand()%100+1;
        printf("\nA közönség szavazása:\n");
        if(esely<91){                               // 90%-os eséllyel helyes válasz
            int hova=kerdes->valasz-'A';            //0-3
            int honnan;
            int temp_max=-1;
            for(int i=0;i<4;i++){
                if(arany[i]>temp_max){
                    temp_max=arany[i];              // megkeresi a legnagyobb arányt
                    honnan=i;
                }
            }
            int temp=arany[honnan];
            arany[honnan]=arany[hova];              //és megcseréli a jó válasz arányával
            arany[hova]=temp;
            for(int i=0;i<4;i++){
                printf("%c: %d %%\n",'A'+i,arany[i]);
            }
        }else{
            for(int i=0;i<4;i++){
                printf("%c: %d %%\n",'A'+i,arany[i]);   //különben csak kiírja az arányokat sorban
            }
        }
    }
    return 0;
}
