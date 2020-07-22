#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"


void RemoveBlanks (char *str){
    char straux[strlen(str)];
    int i=0,j=0;
    while(str[i]!='\0'){
        if(!(str[i]==' ')){
            straux[j] = str[i];
            j++;
        }
        i++;
    }
    if(straux[j-1]=='\n')
        straux[j-1]='\0';
    else straux[j]='\0';
    strcpy(str,straux);
}


int LeerTxt(char namefile[]){
    FILE *archivo=NULL;
    int flag=2;
    char str[100];
    archivo=fopen(namefile,"r");
    Lugares *places=NULL;
    Camino *path=NULL;


    while(!feof(archivo)){
        fgets(str,100,archivo);
        RemoveBlanks(str);
        printf("%s\n",str);
        if(strlen(str)>1){
            if(strcmp(str,"Lugares")==0){
                printf("Encontre!\n");
                flag=1;
            }
            if(strcmp(str,"Rutas")==0){
                printf("x2\n");
                flag=0;
            }

            if(flag==1){
                if(strcmp(str,"Lugares")!=0 && strlen(str)>1)
                    places=InsertLugar(places,LugarNuevo(str));
            }

            if(flag==0){
                if(strcmp(str,"Rutas")!=0 && strlen(str)>1)
                    path=LeerRuta(str,places,path);
            }

        }

    }
    printf("\n\nLugares:\n");
    ImprimirLugares(places);
    printf("\n\nRutas:\n");
    ImprimirRuta(path);

    return 0;
}

int main(){
    char namefile[100];


    FILE *fp=NULL;
    printf("\nIngrese el documento a agregar\n");
    scanf("%s",namefile);
    fp=fopen(namefile,"r");
    if(fp==NULL){
        if(!strstr(namefile,".txt")){
            strcat(namefile,".txt");
            fp=fopen(namefile,"r");
            if(fp==NULL){
                printf("\nARCHIVO NO ENCONTRADO!\n");
                return 0;
            }
            else fclose(fp);
        }
    }

    LeerTxt(namefile);

}
