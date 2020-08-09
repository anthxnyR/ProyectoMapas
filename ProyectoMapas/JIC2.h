#ifndef JIC2_H_INCLUDED
#define JIC2_H_INCLUDED
#include "Listas.h"

// ************************ ESTRUCTURAS DEFINIDAS ************************

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
    int visited;
    struct Lugares *Next;
}Lugares;

typedef struct Camino{
    char Name[100];
    float Peso[3];
    struct Camino *Next;
    struct Lugares *Ady, *Og;
}Camino;

// ************************ FUNCIONES BASICAS DE LISTAS *****************************************

//LUGARES
Lugares *LugarNuevo(char str[]){
    Lugares *NewLugar=(Lugares *)malloc(sizeof(Lugares));
    if(NewLugar==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }else{
        strcpy(NewLugar->Name,str);
        NewLugar->Next=NULL;
        NewLugar->visited=0;
    }
    return NewLugar;
}

Lugares *InsertLugar(Lugares *Map, Lugares *NewLugar){
    Lugares *ptr;
    if(Map==NULL) return NewLugar;
    for(ptr=Map;ptr->Next;ptr=ptr->Next);
    ptr->Next=NewLugar;
    return Map;
}

Lugares *BuscarNodo(char str[], Lugares *Mapa){
    Lugares *aux=Mapa;
    while(aux){
        if(strcmp(aux->Name,str)==0) return aux;
        aux=aux->Next;
    }
    return NULL;
}

void ImprimirLugares(Lugares *Map){
    while(Map!=NULL){
        printf("%s\n",Map->Name);
        Map=Map->Next;
    }
}

Lugares *FreeLugares(Lugares *places){
    Lugares *next;

    for(;places;places=next){
        next=places->Next;
        free(places);
    }
    return NULL;
}

//CAMINO
Camino *CaminoNuevo(char str[],float P, float B, float C){
    Camino *newCamino=(Camino *)malloc(sizeof(Camino));
    if(newCamino==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }

    else{
        strcpy(newCamino->Name,str);
        newCamino->Peso[0]=P;
        newCamino->Peso[1]=B;
        newCamino->Peso[2]=C;
        newCamino->Ady=NULL;
        newCamino->Next=NULL;
    }
    return newCamino;
}

Camino *AddCamino(Camino *newCamino,char Origen[],char Destino[], Lugares *Mapa,Camino *path){
    Camino *aux=path;
    Lugares *LOrigen, *LDestino;
    LOrigen=BuscarNodo(Origen,Mapa);
    if(!LOrigen){
        printf("\n   ERROR EN: %s\nEL LUGAR NO EXISTE\n",Origen);
        return NULL;
    }
    LDestino=BuscarNodo(Destino,Mapa);
    if(!LDestino){
        printf("\n\t*** ERROR EN: %s ***\n\t  EL LUGAR NO EXISTE\n",Destino);
        return NULL;
    }

    if(aux==NULL){
        path=newCamino;
    }else{
        while(aux->Next) aux=aux->Next;
        aux->Next=newCamino;
    }

    newCamino->Og=LOrigen;
    newCamino->Ady=LDestino;
    return path;

}

void ImprimirRuta(Camino *path){
    while(path!=NULL){
        printf("%s->%s:%s=P:%.1f;B:%.1f;C:%.1f\n",path->Name,path->Og->Name,path->Ady->Name,path->Peso[0],path->Peso[1],path->Peso[2]);
        path=path->Next;
    }
}

Camino *FreeCamino(Camino *path){
    Camino *next;
    for(;path;path=next){
        next=path->Next;
        free(path);
    }
    return NULL;
}

//TRAYECTO
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

Trayecto *copylist(Trayecto *listp){
    Trayecto *copylistp=NULL;
    Trayecto *p=listp;
    while(p!=NULL){
        copylistp=AddTrayecto(copylistp,NuevoTrayecto(p->path));
        p=p->next;
    }
    return copylistp;
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

Trayecto *FreeTrayecto(Trayecto *tray){
    Trayecto *next;
    for(;tray;tray=next){
        next=tray->next;
        free(tray);
    }
    return NULL;
}

//MAPA
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

Mapa *FreeMapa(Mapa *Map){
    Mapa *next;

    for(;Map;Map=next){
        next=Map->next;
        free(Map);
    }
    return NULL;
}

// **************************FIN DE FUNCIONES BASICAS DE LISTAS  **************************

//Verifica que si el trayecto es en su totalidad transitable
int CheckPath(Trayecto *tray, int idx){
    Trayecto *aux=tray;
    for(;aux;aux=aux->next)
        if(aux->path->Peso[idx]==0)
            return 0;
    return 1;
}

//Obtiene el peso Total de un trayecto entre dos puntos
float PesoTotal(Trayecto *tray,int idx){
    if(!tray) return 0;
    Trayecto *aux=tray;
    float suma=0;
    int flag;
    flag=CheckPath(aux,idx);
    while(aux){
        if(flag) suma+=aux->path->Peso[idx];
        else return suma;
        aux=aux->next;
    }

    return suma;
}

//Ordena todas las rutas de Menor a Mayor, obteniendo las dos mas optimas de primeras.
Mapa *OrdenarMapa(Mapa *Map,int idx){
    if(!Map) return NULL;
    for(;;){
        int cambio = 0;
        Mapa **linkp = &Map;
        Mapa *curr = Map;
        Mapa *nextnode;

        while(nextnode=curr->next){
            if(PesoTotal(curr->viaje,idx)>PesoTotal(nextnode->viaje,idx)){
                curr->next=nextnode->next;
                nextnode->next=curr;
                *linkp=curr=nextnode;
                cambio++;
            }
            linkp = &curr->next;
            curr=nextnode;
        }
        if(cambio==0)
            break;
    }
    return Map;
}

//Imprime el trayecto con un formato dado
void ImprimirTrayecto(Trayecto *Tray,int idx){
    Trayecto *aux;
    float acumulador=0,auxacum=0;
    switch (idx){
        case 0:
            aux=Tray;
            printf("Ruta a Pie:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,idx)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[idx],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[idx];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Pie: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino a Pie!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            break;

        case 1:
            acumulador=0;
            aux=Tray;
            printf("Ruta a Autobus:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,idx)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[idx],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[idx];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Autobus: %.1f\n\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino por Autobus!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            break;

        case 2:
            acumulador=0;
            aux=Tray;
            printf("Ruta a Carro:\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
            if(CheckPath(aux,idx)){
                while(aux){
                    printf("%s -> %s  \t\t  Tiempo: %.1f  \t\t  A traves de %s",aux->path->Og->Name,aux->path->Ady->Name,aux->path->Peso[idx],aux->path->Name);
                    printf("\n");
                    acumulador+=aux->path->Peso[idx];
                    aux=aux->next;
                }
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                printf("\t\t\tCosto Total a Carro: %.1f\n\n",acumulador);
                auxacum+=acumulador;
            }else{
                printf("\t\tNo existe un camino por Carro!\n");
                printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n\n");
            }
            break;
    }
    //printf("COSTO TOTAL: %.1f\n\n\n\n",auxacum);
    return;
}

void Impresionmqm(Trayecto *tray){
    if(!tray) return;
    Trayecto *aux=tray;
    while(aux){
        printf("%s\n",aux->path->Name);
        aux=aux->next;
    }
}

void ImprimirMapa(Mapa *Map){
    if(!Map) return;
    int i=1;
    Mapa *aux=Map;
    while(aux){
        printf("Ruta %d\n",i++);
        Impresionmqm(aux->viaje);
        aux=aux->next;
        printf("\n");
    }
}

//Solo imprime las dos primeras rutas del mapa, en caso que no existan o falte alguna, avisa
void ImpresionDosRutas(Mapa *Map,char Origen[],char Destino[],int idx){
    if(!Map){
        system("clear");
        printf("\n\n** NO EXISTEN RUTAS PARA ESTE VIAJE **\n");
        getchar();
        return;
    }
    char *typepath[3];
    typepath[0]="PIE";
    typepath[1]="AUTOBUS";
    typepath[2]="CARRO";
    Mapa *aux=Map;
    while(aux){
        if(CheckPath(aux->viaje,idx)){
            system("clear");
            printf("\n\t\tRUTA MAS OPTIMA A %s DE ''%s'' A ''%s'': \n\n",typepath[idx],Origen,Destino);
            ImprimirTrayecto(aux->viaje,idx);
            break;
        }
        else aux=aux->next;
    }
    if(!aux){
        system("clear");
        printf("\n\n** NO EXISTEN RUTAS PARA A %s ESTE VIAJE **\n",typepath[idx]);
        return;
    }
    aux=aux->next;
    while(aux){
        if(CheckPath(aux->viaje,idx)){
            printf("\n\t\tSEGUNDA RUTA A %s MAS OPTIMA DE ''%s'' A ''%s'': \n\n",typepath[idx],Origen,Destino);
            ImprimirTrayecto(aux->viaje,idx);
            break;
        }
        else aux=aux->next;
    }
    return;
}
#endif // JIC2_H_INCLUDED
