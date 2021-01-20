#include <stdio.h>
#include "dicsoseg.h"
#include <string.h>

int dicsoseg_ir(char* nev, int nyeremeny,unsigned ido, int segitsegek){
    FILE* dics;
    dics= fopen("dicsoseg.txt","r");
    if(dics==NULL){
        dics=fopen("dicsoseg.txt","w");
        if(strlen(nev)<8){
                if(nyeremeny>1500000){
                    fprintf(dics,"1\t\t%s\t\t\t%d\t\t%d\t\t%d\n",nev,nyeremeny,segitsegek,ido);
                }else fprintf(dics,"1\t\t%s\t\t\t%d\t\t\t%d\t\t%d\n",nev,nyeremeny,segitsegek,ido);
            }
        else{
            if(nyeremeny>1500000){
                    fprintf(dics,"1\t\t%s\t\t%d\t\t%d\t\t%d\n",nev,nyeremeny,segitsegek,ido);
                }else fprintf(dics,"1\t\t%s\t\t%d\t\t\t%d\t\t%d\n",nev,nyeremeny,segitsegek,ido);
            }
        for(int i=2;i<=20;i++){
            fprintf(dics,"%d\t\t.\t\t\t-1\t\t\t4\t\t10\n",i);
        }
        printf("\nMég nem volt létrehozva dicsőséglista, ezért a program létrehozta.");
    }else{
        Dicsoseg lista[20];
        for(int i=0;i<20;i++){
            fscanf(dics, "%d", &lista[i].helyezes);
            char temp;
            while(fscanf(dics,"%c",&temp) && temp=='\t');
            ungetc(temp,dics);
            int j=0;
            while(fscanf(dics,"%c",&lista[i].nev[j]) && lista[i].nev[j]!='\t'){j++;}
            lista[i].nev[j]='\0';
            j=0;
            fgetc(dics);
            fscanf(dics, "%d", &lista[i].nyeremeny);
            fgetc(dics);
            fscanf(dics, "%d", &lista[i].segitsegek);
            fgetc(dics);
            fscanf(dics, "%ud", &lista[i].ido);
            fgetc(dics);
        }
        printf("\n");
        int n=20;
        for(int i=0;i<20;i++){
            if(nyeremeny>=lista[i].nyeremeny){
                if(nyeremeny>lista[i].nyeremeny){
                    n=i;
                    goto beilleszt;
                }
                for(int j=i;j<20;j++){
                    if(segitsegek<=lista[j].segitsegek){
                        if(segitsegek<lista[j].segitsegek){
                            n=j;
                            goto beilleszt;
                        }
                        for(int k=j;k<20;k++){
                            if(ido<=lista[k].ido){
                                n=k;
                                beilleszt:printf("\nGratulálunk, felkerültél a dicsőséglista %d. helyére!\n",n+1);
                                for(int l=19;l>n;l--){
                                    lista[l]=lista[l-1];
                                }
                                for(int m=0;m<50;m++){
                                    lista[n].nev[m]=nev[m];
                                }
                                lista[n].nyeremeny=nyeremeny;
                                lista[n].segitsegek=segitsegek;
                                lista[n].ido=ido;
                                goto p;
                            }
                        }
                    }
                }
            }

        }
        printf("\nSajnos nem kerültél fel a dicsőséglistára.\n");
        return 8;
        p:if(1);
        for(int i=0;i<20;i++){
            lista[i].helyezes=i+1;
        }

        dics=fopen("dicsoseg.txt","w");
        for(int i=0;i<20;i++){
            if(strlen(lista[i].nev)<8){
                if(lista[i].nyeremeny>1500000){
                    fprintf(dics,"%d\t\t%s\t\t\t%d\t\t%d\t\t%d\n",lista[i].helyezes,lista[i].nev,lista[i].nyeremeny,lista[i].segitsegek,lista[i].ido);
                }else fprintf(dics,"%d\t\t%s\t\t\t%d\t\t\t%d\t\t%d\n",lista[i].helyezes,lista[i].nev,lista[i].nyeremeny,lista[i].segitsegek,lista[i].ido);
            }
            else{
                if(lista[i].nyeremeny>1500000){
                    fprintf(dics,"%d\t\t%s\t\t%d\t\t%d\t\t%d\n",lista[i].helyezes,lista[i].nev,lista[i].nyeremeny,lista[i].segitsegek,lista[i].ido);
                }else fprintf(dics,"%d\t\t%s\t\t%d\t\t\t%d\t\t%d\n",lista[i].helyezes,lista[i].nev,lista[i].nyeremeny,lista[i].segitsegek,lista[i].ido);
            }
        }
    }
    fclose(dics);
    return 0;
}

int dicsoseg_olvas(){
    FILE* dics;
    dics= fopen("dicsoseg.txt","r");
    if(dics==NULL){
            printf("A program nem talált dicsőséglistát.\n");
            return 2;
    }else{
        printf("Helyezés\tNév\t\t\tNyeremény\tFelhasznált segítségek\tJátékidő\n");
        char temp;
        while(temp!=EOF){
            temp=fgetc(dics);
            if(temp=='\n'){
                printf(" perc");
            }
            printf("%c",temp);
        }
        fclose(dics);
        return 0;
    }
}
