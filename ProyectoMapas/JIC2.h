#ifndef JIC2_H_INCLUDED
#define JIC2_H_INCLUDED
#include "Listas.h"

typedef struct Trayecto{
    struct Camino *path;
    struct Trayecto *next;
}Trayecto;

typedef struct Mapa{
    struct Trayecto *viaje;
    struct Mapa *next;
}Mapa;

typedef struct Lugares{
    char Name[100];
    struct Lugares *Next;
}Lugares;

typedef struct Camino{
    char Name[100];
    float Peso[3];
    struct Camino *Next;
    struct Lugares *Ady, *Og;
}Camino;

Trayecto *NuevoTrayecto(Camino *ruta){
    Trayecto *NewTray = (Trayecto *)malloc(sizeof(Trayecto));
    if(NewTray==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }else{
        NewTray->path=ruta;
        NewTray->next=NULL;
    }
    return NewTray;
}

Trayecto *AddTrayecto(Trayecto *Tray,Trayecto *newTray){
    Trayecto *Aux=Tray;
 		if (Tray ==NULL )
	    	return newTray ;
        while(Aux->next!=NULL)
            Aux=Aux->next;

 		Aux->next=newTray ;
 		return Tray;
}

Trayecto *DeleteLast(Trayecto *Tray){
    if(!Tray) return Tray;
    if(!Tray->next){
        free(Tray);
        Tray=NULL;
        return Tray;
    }

    Trayecto *aux=Tray;
    while(aux->next->next)
        aux=aux->next;

    free(aux->next);
    aux->next=NULL;
    return Tray;
}

Mapa *NuevoMapa(Trayecto *tray){
    Mapa *newMap = (Mapa *)malloc(sizeof(Mapa));
    if(newMap==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }else{
        newMap->viaje=tray;
        newMap->next=NULL;
    }
    return newMap;
}

Mapa *AddMapa(Mapa *Map, Mapa *newMap){
    Mapa *Aux=Map;
 		if (Map ==NULL )
	    	return newMap ;

 		while(Aux->next!=NULL)
            Aux=Aux->next;

 		Aux->next=newMap;
 		return Map;
}

int CheckPath(Trayecto *tray, int i){
    Trayecto *aux=tray;
    for(;aux;aux=aux->next)
        if(aux->path->Peso[i]==0)
            return 0;
    return 1;
}

int checklen(char str[]){
    int cont=0;
    for(int i=0;str[i]!='\0';i++)
        cont++;
    return cont;
}

int VerificarTxt(char str[]){
    int len=checklen(str);
    for(int i=0;i<len;i++)
        if(!isalnum(str[i]) && str[i]!='_')
            return 0;
    return 1;
}

void ImprimirTrayecto(Trayecto *Tray){
    Trayecto *aux;
    float acumulador=0,auxacum=0;
    int i=0;
    switch (i){
        case 0:
            aux=Tray;
            printf("Ruta a Pie:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,i)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[i];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Pie: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino a Pie!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            i++;

        case 1:
            acumulador=0;
            aux=Tray;
            printf("Ruta a Autobus:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,i)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[i];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Autobus: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino por Autobus!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            i++;

        case 2:
            acumulador=0;
            aux=Tray;
            printf("Ruta a Carro:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,i)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[i];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Carro: %.1f\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino por Carro!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            i++;
    }
    printf("COSTO TOTAL: %.1f\n\n\n\n",auxacum);
    return;
}

float PesoTotal(Trayecto *tray){
    if(!tray) return 0;
    Trayecto *aux=tray;
    float suma=0;
    while(aux){
        suma+=(aux->path->Peso[0])+(aux->path->Peso[1])+(aux->path->Peso[2]);
        aux=aux->next;
    }
    return suma;
}

Mapa *OrdenarMapa(Mapa *Map){
    if(!Map) return Map;
    if(!Map->next) return Map;
    float menor=0,comp=0;
    Mapa *curr=Map,*aux,*prev;
    int done=0;
    while(curr){
        curr=prev=Map;
        while(curr && curr->next){
            if(PesoTotal(curr->viaje)>PesoTotal(curr->next->viaje)){
                aux=curr->next;
                curr->next=curr->next->next;
                aux->next=curr;
                if(Map==curr)Map=prev=aux;
                else{
                    prev->next=aux;
                    curr=aux;
                }
            }
            prev=curr;
            curr=curr->next;
        }
    }
    return Map;
}



void ImpresionDosRutas(Mapa *Map,char Origen[],char Destino[]){
    if(!Map){
        system("clear");
        printf("\n\n** NO EXISTEN RUTAS PARA ESTE VIAJE **\n");
        getchar();
        return;
    }
    Mapa *aux=Map;
    system("clear");
    printf("\n\t\tRUTA MAS OPTIMA DE ''%s'' A ''%s'': \n\n",Origen,Destino);
    ImprimirTrayecto(aux->viaje);
    aux=aux->next;
    printf("\nPresione Enter para continuar");
    getchar();
    getchar();
    if(aux){
        printf("\n\t\tSEGUNDA RUTA MAS OPTIMA DE ''%s'' A ''%s'': \n\n",Origen,Destino);
        ImprimirTrayecto(aux->viaje);
    }else{
        system("clear");
        printf("\n\n** NO EXISTE UNA SEGUNDA RUTA OPTIMA **\n");
    }
    return;


}
#endif // JIC2_H_INCLUDED
