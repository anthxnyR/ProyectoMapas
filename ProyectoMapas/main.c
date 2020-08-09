#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Listas.h"

//******************************** FUNCIONES QUE LEEN EL CLIMA Y ALMACENAN EN MEMORIA ********************
int PasarClima(char ogstr[], Camino *path){
    char str[100],str_aux[100],nombre[100],num;
    float P,B,C;
    strcpy(str,ogstr);
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
    return 1;
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
    return 1;
}

//******************************* FIN DE FUNCIONES DEL CLIMA ********************************


//Busca todas las rutas posibles en el Mapa y las almacena en memoria
Mapa *BuscarRutas(Camino *path,char Origen[],char Destino[], Trayecto *tray, Mapa *Map){
    Camino *aux=path;
    if(path==NULL) return Map;
    for(;aux;aux=aux->Next){
        if((aux->Peso[0]+aux->Peso[1]+aux->Peso[2])==0) return Map;
        if(strcmp(aux->Og->Name,Origen)==0){
            aux->Og->visited=1;
            tray=AddTrayecto(tray,NuevoTrayecto(aux));
            if(strcmp(aux->Ady->Name,Destino)==0){
                Trayecto *ptr=copylist(tray);
                Map=AddMapa(Map,NuevoMapa(ptr));
            }
            else if(aux->Ady->visited!=1) Map=BuscarRutas(path,aux->Ady->Name,Destino,tray,Map);
            tray=DeleteLast(tray);
            aux->Og->visited=0;
        }
    }
    return Map;
}

//FUncion de Inicio del Menu
int StartApp(){
    char namefile[100],Origen[50],Destino[50];
    int option;
    char opt;
    FILE *archivo=NULL;
    int flag=2,admitido=1;
    char str[100];
    Lugares *places=NULL;
    Camino *path=NULL;

    printf("\n\n\t\t*********BIENVENIDO A AYPII MAPS*********\n\n");
    while(option!=3){
        printf("Ingrese la opcion que desee:\n\n");
        printf("\t[1] Agregar un Mapa\n");
        printf("\t[2] Consultar una ruta\n");
        printf("\t[3] Salir del Programa\n\n");
        scanf("  %i",&option);
        switch(option){
            case 1:
                admitido=1;
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
                            getchar();
                            getchar();
                            system("clear");
                            break;
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
                            if(VerificarTxt(str)){
                                if(strcmp(str,"Lugares")!=0 && strlen(str)>1)
                                places=InsertLugar(places,LugarNuevo(str));
                            }else{
                                system("clear");
                                printf("\n     ERROR EN LUGAR: %s. \nSOLO SE ADMITEN CARACTERES ALFANUMERICOS Y '_' \n\n",str);
                                places=FreeLugares(places);
                                admitido=0;
                                break;
                            }
                        }

                        if(flag==0){
                            if(strcmp(str,"Rutas")!=0 && strlen(str)>1){
                                path=LeerRuta(str,places,path);
                                if(!path){
                                    printf("EN LA SIGUIENTE ENTRADA: %s\n",str);
                                    places=FreeLugares(places);
                                    admitido=0;
                                    break;
                                }
                            }
                        }

                    }

                }
                fclose(archivo);
                if(admitido){
                    char *option,nameclima[50];
                    printf("\nDesea ingresar un archivo de clima? (Y/N)\n");
                    do{
                        scanf("\n%c",&opt);
						system("clear");
                        if(toupper(opt)=='Y'){
                            system("clear");
                            printf("Ingrese el archivo que desea leer\n");
                            scanf("\n%s",nameclima);
                            archivo=fopen(nameclima,"r");
                            if(archivo==NULL){
                                if(!strstr(nameclima,".txt")){
                                    strcat(nameclima,".txt");
                                    archivo=fopen(nameclima,"r");
                                    if(archivo==NULL){
                                        printf("\nARCHIVO NO ENCONTRADO!\n");
                                        getchar();
                                        getchar();
                                        system("clear");
                                        break;
                                    }
                                    else fclose(archivo);
                                }
                            }
                            if(!VerifyTxtClima(nameclima)){
                                printf("\n\t\tEl clima no fue agregado!");
                                getchar();
                                getchar();
                            }else{
                                LeerClima(nameclima,path);
                            }
                        }else if(toupper(opt)=='N'){
                            getchar();
                        }else if (toupper(opt)!='N' && toupper(opt)!='S'){
                            printf("\n\n\t\tOPCION INVALIDA, VUELVA A INTENTARLO!\n\n");
						}
                    }while(toupper(opt)!='N' && toupper(opt)!='Y');
                    system("clear");
                    printf("\nDocumento agregado con exito!\n");
                    printf("\nLugares:\n");
                    ImprimirLugares(places);
                    printf("\n");
                    printf("\nRutas:\n");
                    ImprimirRuta(path);
                }
                printf("\nPulse Enter para continuar\n");
                printf("\n");
                getchar();
                getchar();
                system("clear");
                break;
            case 2:
                system("clear");
                printf("Ingrese la ruta que desea consultar\n\n");
                if(!places) printf("\n\n\n\n\t\tNO HAY NINGUN MAPA CARGADO\n\n\n\n");
                else{
                    ImprimirLugares(places);
                    printf("\n\nOrigen > ");
                    scanf(" %s",Origen);
                    if(!Existe(Origen,places)){
                        printf("\n***** EL LUGAR DE ORIGEN NO EXISTE *****\n");
                        getchar();
                        getchar();
                        system("clear");
                        break;
                    }
                    printf("Destino > ");
                    scanf(" %s",Destino);
                    if(Existe(Destino,places)==0){
                        printf("\n***** EL LUGAR DE DESTINO NO EXISTE *****\n");
                        getchar();
                        getchar();
                        system("clear");
                        break;
                    }
                    Trayecto *tray=NULL;
                    Mapa *Map=NULL;
                    Map=BuscarRutas(path,Origen,Destino,tray,Map);
                    Map=OrdenarMapa(Map,0);
                    ImpresionDosRutas(Map,Origen,Destino,0);
                    printf("\n\n\t\tPresione Enter para continuar.\n");
                    getchar();
                    getchar();
                    Map=OrdenarMapa(Map,1);
                    ImpresionDosRutas(Map,Origen,Destino,1);
                    printf("\n\n\t\tPresione Enter para continuar.\n");
                    getchar();
                    getchar();
                    Map=OrdenarMapa(Map,2);
                    ImpresionDosRutas(Map,Origen,Destino,2);
                    tray=FreeTrayecto(tray);
                    Map=FreeMapa(Map);
                }
                printf("\n");
                printf("\t\tPresione Enter para continuar.\n");
                getchar();
                getchar();
                system("clear");
                break;
            case 3:
                system("clear");
                places=FreeLugares(places);
                path=FreeCamino(path);
                printf("\n\n\n\n\n\n\n\n\t\t***GRACIAS POR PREFERIRNOS***\n\t     Vuelva pronto y maneje con cuidado!\n\n\n\n\n\n\n\n");
                getchar( );
                getchar();
                break;
        }
    }
}

int main(){
    system("clear");
    StartApp();
}
