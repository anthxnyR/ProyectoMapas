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
    //struct Camino *Ady; creo que no es necesario.
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
    Trayecto *aux=Tray;
    printf("Trayecto:\n");
    while(aux!=NULL){
        printf("%s \n",aux->path->Name);
        aux=aux->next;
    }
    printf("\n");
    return;
}

void ImprimirMapas(Mapa *Map){
    while(Map!=NULL){
        printf("\nMapa::\n");
        ImprimirTrayecto(Map->viaje);
        Map=Map->next;
    }
}

#endif // JIC2_H_INCLUDED
