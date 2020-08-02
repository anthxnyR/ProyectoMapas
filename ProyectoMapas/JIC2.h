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

void ImprimirTrayecto(Trayecto *Tray){
    Trayecto *aux;
    float acumulador=0,auxacum=0;
    int i=0;
    switch (i){
        case 0:
            aux=Tray;
            if(aux->path->Peso[i]>0){
                printf("Ruta a Pie:\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                while(aux){
                    //if(aux->path->Peso[i]>0){
                        printf("%s -> %s  **  Tiempo: %.1f  **  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                        printf("\n");
                        acumulador+=aux->path->Peso[i];
                        aux=aux->next;
                    //}
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("Costo Total a Pie: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }
            i++;

        case 1:
            acumulador=0;
            aux=Tray;
            if(aux->path->Peso[i]>0){
                printf("Ruta a Autobus:\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                while(aux){
                    printf("%s -> %s  **  Tiempo: %.1f  **  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[i];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("Costo Total a Autobus: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }
            i++;

        case 2:
            acumulador=0;
            aux=Tray;
            if(aux->path->Peso[i]>0){
                printf("Ruta a Carro:\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                while(aux){
                    printf("%s -> %s  **  Tiempo: %.1f  **  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[i],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[i];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("Costo Total a Carro: %.1f\n\n",acumulador);
                auxacum+=acumulador;
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
    Mapa *aux=Map;
    system("clear");
    printf("\n       RUTA MAS OPTIMA DE ''%s'' A ''%s'': \n\n",Origen,Destino);
    ImprimirTrayecto(aux->viaje);
    aux=aux->next;
    printf("\n       SEGUNDA RUTA MAS OPTIMA DE ''%s'' A ''%s'': \n\n",Origen,Destino);
    ImprimirTrayecto(aux->viaje);
    return;


}
#endif // JIC2_H_INCLUDED
