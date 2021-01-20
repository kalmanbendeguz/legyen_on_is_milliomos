#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "jatek.h"
#include "segitseg.h"
#include "sorkerdes.h"
#include "dicsoseg.h"

int felszabadit(Kerdes* kerdes, int kerdesszam){
    Kerdes* iter = kerdes;
    for(int i=0;i<kerdesszam;i++){
        Kerdes *kov = iter->kov;
        free(iter);
        iter=kov;
    }
    return 0;
}

int segitsegszam(bool* segitsegek){
    int mennyi=0;
    for(int i=0;i<3;i++){
        if(segitsegek[i]){
            mennyi++;
        }
    }
    return mennyi;
}

int jatek(){
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif
    srand(time(NULL));
    char temp[2]; //majd amikor a segitseg függvénynek nem lesz feladata visszaadni a két megmaradt karaktert (mert nem a felezést választjuk), akkor ide olvassuk be
    if(sorkerdes()!=0){
        printf("Gond volt a sorkérdésekkel.\n");
        return 3;
    }
    int nyeremenyek[15]={5000,10000,25000,50000,100000,200000,300000,500000,800000,1500000,3000000,5000000,10000000,20000000,40000000};
    int stabilnyeremenyek[15]={0,0,0,0,100000,100000,100000,100000,100000,1500000,1500000,1500000,1500000,1500000,40000000};
    Kerdes* kerdes1;
    char* elsosor=(char*) malloc(1000*sizeof(char));
    if(elsosor==NULL){
        printf("Nem sikerült memóriát foglalni!\n");
        return 1;
    }
    kerdes1= (Kerdes*) malloc(sizeof(Kerdes));
    if(kerdes1==NULL){
        printf("Nem sikerült memóriát foglalni!\n");
        return 1;
    }
    FILE* fp;
    fp=fopen("loim.txt","r");
    if(fp==NULL){
        printf("Nem sikerült megnyitni a fájlt!\n");
        return 2;
    }
    fgets(elsosor, 1000, fp);   //a fájl első sorát beolvassuk
    free(elsosor);              //és eldobjuk
    int kerdesszam=0;
    Kerdes* mozgo = kerdes1;
    while(true){
        fscanf(fp, "%d", &mozgo->nehezseg);
        fgetc(fp);
        int i=0;
        while(fscanf(fp,"%c",&mozgo->kerdess[i]) && mozgo->kerdess[i]!='\t'){i++;}
        mozgo->kerdess[i]='\0';
        i=0;
        while(fscanf(fp,"%c",&mozgo->a[i]) && mozgo->a[i]!='\t'){i++;}
        mozgo->a[i]='\0';
        i=0;
        while(fscanf(fp,"%c",&mozgo->b[i]) && mozgo->b[i]!='\t'){i++;}
        mozgo->b[i]='\0';
        i=0;
        while(fscanf(fp,"%c",&mozgo->c[i]) && mozgo->c[i]!='\t'){i++;}
        mozgo->c[i]='\0';
        i=0;
        while(fscanf(fp,"%c",&mozgo->d[i]) && mozgo->d[i]!='\t'){i++;}
        mozgo->d[i]='\0';
        fscanf(fp, "%c", &mozgo->valasz);
        i=0;
        fscanf(fp, "%s", &mozgo->kategoria);
        kerdesszam++;
        if(fgetc(fp)==EOF){         //ha az utolsó kérdést is beolvastuk,
            mozgo->kov = kerdes1;   //hozzáfűzzük a lista utolsó elemének pointerét a lista elejéhez
            break;                  //ezután már nincs szükség további foglalásra
        }
        mozgo->kov = (Kerdes*) malloc(sizeof(Kerdes));
        if(mozgo->kov==NULL){
            printf("Nem sikerült memóriát foglalni!\n");
            return 1;
        }
        mozgo=mozgo->kov;
    }
    fclose(fp);
    Kerdes* mozgo1= kerdes1;
    printf("\n%d kérdést sikerült beolvasni.\n\n",kerdesszam);
    Jatekos jatekos;
    jatekos.segitsegek[0]=false;
    jatekos.segitsegek[1]=false;
    jatekos.segitsegek[2]=false;
    printf("Írd be a neved: ");
    getchar();
    scanf("%[^\n]", jatekos.nev);
    printf("A neved: [%s]\n",jatekos.nev);
    int nehezseg_val;
    int nehezsegek[5][3]={{1,2,3},{3,4,5},{5,6,7},{8,9,10},{10,11,12}}; //a különböző szintekhez tartoznak 5-5-5 kérdés a 3 nehézségből (lásd 126. sor)
    printf("Milyen nehézségen szeretnél játszani? (1-5)\n");
    neh:scanf("%d",&nehezseg_val);
    if(nehezseg_val<1 || nehezseg_val>5){
        printf("Ilyen nehézséget nem választhatsz, írj be számot 1 és 5 között!\n");
        goto neh;
    }
    scanf("%*[^\n]%*c");
    unsigned seconds_start;
    seconds_start = time(NULL);
        for(int k=0;k<15;k++){
                int nehezseg_tenyleges=nehezsegek[nehezseg_val-1][k/3];
                int rand_kerdes=rand()%kerdesszam;
                for(int j=0;j<rand_kerdes;j++){
                    mozgo1=mozgo1->kov;
                }
                while(mozgo1->volt_e || mozgo1->nehezseg!=nehezseg_tenyleges){  //ha volt már a kérdés, vagy a nehézség nem megfelelő
                    int rand_kerdes2=rand()%kerdesszam;                         //új kérdést sorsolunk
                    for(int j=0;j<rand_kerdes2;j++){
                        mozgo1=mozgo1->kov;                                     //és odalépünk a láncolt listán
                    }
                }
            mozgo1->volt_e=true;
            char valasztas;
            getchar();
            printf("\n%d. kérdés\nKategória: %s\n%s\nA: %s\nB: %s\nC: %s\nD: %s\n",k+1,mozgo1->kategoria, mozgo1->kerdess, mozgo1->a,mozgo1->b,mozgo1->c,mozgo1->d);
            printf("[%c]\n",mozgo1->valasz);
            valasz:valasztas=getchar();
            valasztas=toupper(valasztas);
            f:switch (valasztas){
                case 'F':
                    if(!jatekos.segitsegek[0]){
                        char megmaradtak[2];
                        jatekos.segitsegek[0]=true;
                        getchar();
                        if(segitseg(mozgo1,'F', megmaradtak)==0){
                            printf("Ezt figyelembe véve, mit válaszolsz?\n");
                            valasztas=getchar();
                            valasztas = toupper(valasztas);
                            if(!(valasztas==megmaradtak[0] || valasztas==megmaradtak[1] || valasztas=='M' || valasztas=='T' || valasztas=='K')){
                                getchar();
                                printf("Érvénytelen válasz, írj be valami mást!\n");
                                valasztas=getchar();
                                valasztas=toupper(valasztas);
                                goto valasz;
                            }
                        }
                    }else{
                        getchar();
                        printf("Sajnos a felezést már felhasználtad.\n");
                        valasztas=getchar();
                        valasztas = toupper(valasztas);
                        goto f;
                    };
                    break;
                case 'T':
                    if(!jatekos.segitsegek[1]){
                        jatekos.segitsegek[1]=true;
                        getchar();
                        if(segitseg(mozgo1,'T',temp)==0){
                        printf("Ezt figyelembe véve, mit válaszolsz?\n");
                        valasztas=getchar();
                        valasztas = toupper(valasztas);
                        }
                    }
                    else{
                        getchar();
                        printf("Sajnos a telefont már felhasználtad.\n");
                        valasztas=getchar();
                        valasztas = toupper(valasztas);
                        goto f;
                    };
                    break;
                case 'K':
                    if(!jatekos.segitsegek[2]){
                        jatekos.segitsegek[2]=true;
                        getchar();
                        if(segitseg(mozgo1,'K',temp)==0){
                        printf("Ezt figyelembe véve, mit válaszolsz?\n");
                        valasztas=getchar();
                        valasztas = toupper(valasztas);
                        }
                    }
                    else{
                        getchar();
                        printf("Sajnos a közönség-segítséget már felhasználtad.\n");
                        valasztas=getchar();
                        valasztas = toupper(valasztas);
                        goto f;
                    };
                    break;
                case 'M':
                    if(k==0){
                        printf("Köszönjük a játékot. A nyereményed: 0 Ft");
                    }else printf("Köszönjük a játékot. A nyereményed: %d Ft", nyeremenyek[k-1]);
                    if(felszabadit(kerdes1,kerdesszam)==0){
                        ;
                    }else{
                        printf("Nem sikerült felszabadítani a memóriát!\n");
                        return 5;
                    }
                    unsigned seconds_end;
                    seconds_end=time(NULL);
                    unsigned seconds=seconds_end-seconds_start; //játék végén megállítjuk az időt, és eltároljuk
                    jatekos.ido = seconds/60;                   //percekben
                    if(k==0){
                        if(dicsoseg_ir(jatekos.nev,0,jatekos.ido,segitsegszam(jatekos.segitsegek))==0)return 0;
                        else{
                            printf("Gond volt a dicsőséglistával.\n");
                            return 4;
                        }
                    }else{
                        if(dicsoseg_ir(jatekos.nev,nyeremenyek[k-1],jatekos.ido,segitsegszam(jatekos.segitsegek))==0)return 0;
                        else{
                            printf("Gond volt a dicsőséglistával.\n");
                            return 4;
                        }
                    }
                    break;
            }
            if(valasztas==mozgo1->valasz){
                printf("Helyes válasz!\nEddigi nyeremény: %d Ft\nFix nyeremény: %d Ft\n",nyeremenyek[k],stabilnyeremenyek[k]);
            }
            else if(valasztas=='A' || valasztas=='B' || valasztas=='C' || valasztas=='D'){
                if(k==0){
                    printf("Rossz válasz. A helyes válasz: %c\nA játéknak vége. :(\nNyeremény: %d Ft",mozgo1->valasz, stabilnyeremenyek[k]);
                }else printf("Rossz válasz. A helyes válasz: %c\nA játéknak vége. :(\nNyeremény: %d Ft",mozgo1->valasz, stabilnyeremenyek[k-1]);

                if(felszabadit(kerdes1,kerdesszam)==0){
                    ;
                    }else{
                        printf("Nem sikerült felszabadítani a memóriát!\n");
                        return 5;
                    }
                unsigned seconds_end;
                seconds_end=time(NULL);
                unsigned seconds=seconds_end-seconds_start;
                jatekos.ido = seconds/60;
                if(dicsoseg_ir(jatekos.nev,stabilnyeremenyek[k-1],jatekos.ido,segitsegszam(jatekos.segitsegek))==0)return 0;
                else{
                    printf("Gond volt a dicsőséglistával.\n");
                    return 4;
                }
            }else{
                printf("Érvénytelen válasz, írj be valami mást!\n");
                goto valasz;
            }
        }
    printf("Gratulálok, megnyerted a fődíjat!");
    unsigned seconds_end;
    seconds_end=time(NULL);
    unsigned seconds=seconds_end-seconds_start; //idő megáll
    jatekos.ido = seconds/60;
    if(dicsoseg_ir(jatekos.nev,nyeremenyek[14],jatekos.ido,segitsegszam(jatekos.segitsegek))==0);
    else{
        printf("Gond volt a dicsőséglistával.\n");
        return 4;
    }

    if(felszabadit(kerdes1,kerdesszam)==0){
        return 0;
    }else{
        printf("Nem sikerült felszabadítani a memóriát!\n");
        return 5;
    }
}
