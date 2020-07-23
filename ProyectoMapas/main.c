#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void CambioClima(Camino *path,float P,float B,float C,char name[]){
    if(path==NULL) return;
    for(;path;path=path->Next){
        if(strcmp(path->Name,name)==0){
            path->Peso[0]=path->Peso[0]*P;
            path->Peso[1]=path->Peso[1]*B;
            path->Peso[2]=path->Peso[2]*C;
        }
    }
}

int PasarClima(char str[], Camino *path){
    char str_aux[100],nombre[100],num;
    float P,B,C;
    strcpy(str_aux,str);

    strtok(str_aux,"=");
    strcpy(nombre,str_aux);
    DeleteChar(str,'=');
    strcpy(str_aux,str);

    int i=0;
    while(i<3){
        strtok(str_aux,":");
        num=str_aux[0];
        switch(num){
            case 'P':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                P=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'B':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                B=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'C':
                DeleteChar(str,':');
                C=atof(str);
                i++;
                break;
        }
    }
    CambioClima(path,P,B,C,nombre);

}

int LeerClima(char namefile[], Camino *path){
    FILE *archivo=NULL;
    char str[100];
    archivo=fopen(namefile,"r");

    while(!feof(archivo)){
        fgets(str,100,archivo);
        RemoveBlanks(str);
        if(strlen(str)>1)
            PasarClima(str,path);
    }
    return 0;
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
        if(strlen(str)>1){
            if(strcmp(str,"Lugares")==0){
                flag=1;
            }
            if(strcmp(str,"Rutas")==0){
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
    fclose(archivo);
    char *option,nameclima[50];
    printf("\nDesea ingresar un archivo de clima? (Y/N)\n");
    scanf(" %c",&option);
    if(toupper(option)=='Y'){
        printf("Ingrese el archivo que desea leer\n");
        scanf("%s",nameclima);
        archivo=fopen(nameclima,"r");
        if(archivo==NULL){
            if(!strstr(nameclima,".txt")){
                strcat(nameclima,".txt");
                archivo=fopen(nameclima,"r");
                if(archivo==NULL){
                    printf("\nARCHIVO NO ENCONTRADO!\n");
                    return 0;
                }
                else fclose(archivo);
            }
        }
    }
    LeerClima(nameclima,path);
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
    scanf("\n%s",namefile);
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
