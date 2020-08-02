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
    fclose(archivo);
    return 0;
}

Mapa *BuscarOptimo(Camino *path,char Origen[],char Destino[], Trayecto *tray, Mapa *Map){
    Camino *aux=path;
    if(path==NULL) return Map;
    for(;aux;aux=aux->Next){
        if((aux->Peso[0]+aux->Peso[1]+aux->Peso[2])==0) return Map;
        if(strcmp(aux->Og->Name,Origen)==0){
            tray=AddTrayecto(tray,NuevoTrayecto(aux));
            if(strcmp(aux->Ady->Name,Destino)==0){
                Trayecto *ptr=copylist(tray);
                Map=AddMapa(Map,NuevoMapa(ptr));
            }
            else Map=BuscarOptimo(path,aux->Ady->Name,Destino,tray,Map);
            tray=DeleteLast(tray);
        }
    }
    return Map;
}

int StartApp(){
    char namefile[100],Origen[50],Destino[50];
    int option;
    FILE *archivo=NULL;
    int flag=2;
    char str[100];
    Lugares *places=NULL;
    Camino *path=NULL;

    printf("*********BIENVENIDO A AYPII MAPS*********\n\n");
    while(option!=3){
        printf("Ingrese la opcion que desee:\n\n");
        printf("[1] Agregar un Mapa\n");
        printf("[2] Consultar una ruta\n");
        printf("[3] Salir del Programa\n\n");
        scanf("  %i",&option);
        switch(option){
            case 1:
                system("clear");
                printf("\nIngrese el documento a agregar\n");
                scanf("\n%s",namefile);
                archivo=fopen(namefile,"r");
                if(archivo==NULL){
                    if(!strstr(namefile,".txt")){
                        strcat(namefile,".txt");
                        archivo=fopen(namefile,"r");
                        if(archivo==NULL){
                            printf("\nARCHIVO NO ENCONTRADO!\n");
                            return 0;
                        }
                        else fclose(archivo);
                    }
                }
                path=FreeCamino(path);
                places=FreeLugares(places);
                archivo=fopen(namefile,"r");
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
                scanf("\n%c",&option);
                if(toupper(option)=='Y'){
                    printf("Ingrese el archivo que desea leer\n");
                    scanf("\n%s",nameclima);
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
                    LeerClima(nameclima,path);
                    getchar();
                }else if(toupper(option)=='N'){
                    getchar();
                }
                printf("\nDocumento agregado con exito!\n");
                ImprimirLugares(places);
                printf("\n");
                ImprimirRuta(path);
                printf("\nPulse Enter para continuar\n");
                printf("\n");
                getchar();
                system("clear");
                break;
            case 2:
                system("clear");
                printf("Ingrese la ruta que desea consultar\n");
                printf("Origen: ");
                scanf(" %s",Origen);
                printf("Destino: ");
                scanf(" %s",Destino);
                Trayecto *tray=NULL;
                Mapa *Map=NULL;
                Map=BuscarOptimo(path,Origen,Destino,tray,Map);
                Map=OrdenarMapa(Map);
                ImpresionDosRutas(Map,Origen,Destino);
                printf("\n");
                getchar();
                getchar( );
                system("clear");
                break;
            case 3:
                system("clear");
                places=FreeLugares(places);
                path=FreeCamino(path);
                printf("   ***GRACIAS POR PREFERIRNOS***\nVuelva pronto y maneje con cuidado!\n\n");
                getchar( );
                break;
        }
    }
}

int main(){
    StartApp();
}
