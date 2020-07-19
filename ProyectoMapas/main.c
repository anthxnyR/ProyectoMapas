#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"

void RemoveBlanks(char *str){
    char straux[strlen(str)];
    int i=0,j=0;
    while(str[i]!='\0'){
        if(!str[i]==' '){
            straux[j] = str[i];
            j++;
        }
        i++;
    }
    straux[j]='\0';
    strcpy(str,straux);
}

int ValidarTxt(char namefile[]){ //no se si esta parte sea la mejor forma de leer
    FILE *archivo=NULL;
    char str[1000];
    char array_str[1000]={" "};
    archivo=fopen(namefile,"r");
    Lugares *places=NULL;
    Camino *camino=NULL;


    while(!feof((archivo))){
        fgets(str,100,archivo);
        RemoveBlanks(str);
        if(strcmp(str,"Lugares")){
            fgets(str,100,archivo);
            while(str!="Rutas"||!feof(archivo)){
                RemoveBlanks(str);
                places=InsertLugar(places,LugarNuevo(str));
                fgets(str,100,archivo);
            }
            if(strcmp(str,"Rutas")){
                fgets(str,100,archivo);
                while(!feof(archivo)){
                    RemoveBlanks(str);
                }
            }
        }

    }
}

int main(){
    char namefile[100];


    printf("Ingrese el nombre del archivo\n");
    scanf("%s",namefile);
    if(!strstr(namefile,".txt"))
        strcat(path,".txt");
    FILE *fp=NULL;
    fp=fopen(namefile,"r");
    if(fp==NULL){
        printf("ARCHIVO NO ENCONTRADO!\n");
        return 0;
    }else fclose(fp);

    ValidarTxt(namefile);

}
