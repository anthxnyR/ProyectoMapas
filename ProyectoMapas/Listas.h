#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct Lugares{
    char Name[100];
    struct Lugares *Next;
    struct Camino *Ady;
}Lugares;

typedef struct Camino{
    char Name[100];
    float Peso[3];
    struct Camino *Next;
    struct Lugares *Ady, *Og;
}Camino;

struct Route{
    struct Camino *path;
    struct Route *next;
}Route;


Lugares *LugarNuevo(char str[]){
    Lugares *NewLugar=(Lugares *)malloc(sizeof(Lugares));
    if(NewLugar==NULL){
        printf("ERROR EN MALLOC\n");
        EXIT_FAILURE;
    }else{
        strcpy(NewLugar->Name,str);
        NewLugar->Next=NULL;
        NewLugar->Ady=NULL;
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

void Imprimir(Lugares *Map){
    while(Map!=NULL){
        printf("%s\n",Map->Name);
        Map=Map->Next;
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

void *AddCamino(Camino *newCamino,char Origen[],char Destino[], Lugares *Mapa){
    Lugares *LOrigen, *LDestino,*Aux;
    LOrigen=BuscarLugar(Origen,Mapa);
    LDestino=BuscarLugar(Destino,Mapa);
    Aux=LOrigen->Ady;

    if(LOrigen->Ady==NULL){
        LOrigen->Ady=newCamino;
        newCamino->Og=LOrigen;
        newCamino->Ady=LDestino;
        return;
    }
    else{
        printf("%s\nxd\n",Aux->Name);
        if(Aux->Next==NULL){

            newCamino->Ady=LDestino;
            newCamino->Og=LOrigen;
            Aux->Next=newCamino;
            return;
        }
    }
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

void LeerRuta(char str[], Lugares *Mapa){
    Camino *path=NULL;
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

    AddCamino(CaminoNuevo(Nombre,P,B,C),Origen,Dest,Mapa);
    return;

}

#endif // LISTAS_H_INCLUDED
