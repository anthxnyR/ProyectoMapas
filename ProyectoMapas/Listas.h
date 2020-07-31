#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct Lugares{
    char Name[100];
    int status;
    float suma_peso;
    struct Camino *ruta_og;
    struct Lugares *Next;
}Lugares;

typedef struct Camino{
    char Name[100];
    float Peso[3];
    struct Camino *Next;
    struct Lugares *Ady, *Og;
}Camino;

struct Route{
    struct Camino *path;
    struct Lugares *next;
}Route;


Lugares *LugarNuevo(char str[]){
    Lugares *NewLugar=(Lugares *)malloc(sizeof(Lugares));
    if(NewLugar==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }else{
        strcpy(NewLugar->Name,str);
        NewLugar->Next=NULL;
        NewLugar->status=0;
        NewLugar->suma_peso=10000;
    }
    return NewLugar;
}

Camino *FreeCamino(Camino *path){
    Camino *next;
    for(;path;path=next){
        next=path->Next;
        free(path);
    }
    return NULL;
}

Lugares *FreeLugares(Lugares *places){
    Lugares *next;

    for(;places;places=next){
        next=places->Next;
        free(places);
    }
    return NULL;
}

Lugares *InsertLugar(Lugares *Map, Lugares *NewLugar){
    Lugares *ptr;
    if(Map==NULL) return NewLugar;
    for(ptr=Map;ptr->Next;ptr=ptr->Next);
    ptr->Next=NewLugar;
    return Map;
}

void ImprimirLugares(Lugares *Map){
    while(Map!=NULL){
        printf("%s\n",Map->Name);
        Map=Map->Next;
    }
}

void ImprimirRuta(Camino *path){
    while(path!=NULL){
        printf("%s->%s:%s=P:%.1f;B:%.1f;C:%.1f\n",path->Name,path->Og->Name,path->Ady->Name,path->Peso[0],path->Peso[1],path->Peso[2]);
        path=path->Next;
    }
}

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

Lugares *BuscarLugar(char str[], Lugares *Mapa){
    while(Mapa){
        if(strcmp(Mapa->Name,str)==0) return Mapa;
        Mapa=Mapa->Next;
    }
    return NULL;
}

Camino *AddCamino(Camino *newCamino,char Origen[],char Destino[], Lugares *Mapa,Camino *path){
    Camino *aux=path;
    Lugares *LOrigen, *LDestino;
    LOrigen=BuscarLugar(Origen,Mapa);
    LDestino=BuscarLugar(Destino,Mapa);

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

void DeleteChar(char str[],char const delim){
    int i;
    for(i=0;str[i]!=delim;i++){
        str[i]=' ';
    }
    str[i]=' ';
    RemoveBlanks(str);
    return;
}

Camino *LeerRuta(char str[], Lugares *Mapa, Camino *path){
    char Nombre[100],Origen[100],Dest[100],num;
    char str_aux[100];
    float P,B,C;
    strcpy(str_aux,str);

    strtok(str_aux,"->");
    strcpy(Nombre,str_aux);
    DeleteChar(str,'>');
    strcpy(str_aux,str);

    strtok(str_aux,":");
    strcpy(Origen,str_aux);
    DeleteChar(str,':');
    strcpy(str_aux,str);

    strtok(str_aux,"=");
    strcpy(Dest,str_aux);
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

    path=AddCamino(CaminoNuevo(Nombre,P,B,C),Origen,Dest,Mapa,path);
    return path;

}

#endif // LISTAS_H_INCLUDED
