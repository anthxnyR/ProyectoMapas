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
    Lugares *Aux=Mapa;
    while(Aux){
        if(strcmp(Aux->Name,str)==0) return Aux;
        Aux=Aux->Next;
    }
    return NULL;
}

void *AddCamino(Camino *newCamino,char Origen[],char Destino[], Lugares *Mapa){
    Lugares *AuxOrigen, *AuxDestino;
    AuxOrigen=BuscarLugar(Origen,Mapa);
    AuxDestino=BuscarLugar(Destino,Mapa);

    if(AuxOrigen->Ady==NULL){
        AuxOrigen->Ady=newCamino;
        newCamino->Og=AuxOrigen;
        newCamino->Ady=AuxDestino;
        return;
    }else{
        while(AuxOrigen->Next){
            newCamino->Ady=AuxDestino;
            AuxOrigen->Next=newCamino;
            newCamino->Og=AuxOrigen;
            AuxOrigen=AuxOrigen->Next;
        }
        return;
    }

}

/*void LeerRuta(char str[], Lugares *Mapa){
    Camino *path=NULL;
    char *Nombre,*Origen,*Dest,*num;
    float P,B,C;

    if(strcpy(Nombre,strtok(str,"->"))){
        if(strcpy(Origen,strtok(str,":"))){
            if(strcpy(Dest,strtok(str,"="))){
                if(strtok(str,":")=="P"){
                    if(strcpy(num,strtok(str,";"))<58 && num>47)
                        P=atof(num);
                    if(strtok(str,":")=="B"){
                        if(strcpy(num,strtok(str,";"))<58 && num>47)
                            B=atof(num);
                        if(strtok(str,":")=="C"){
                            if(strcpy(num,strtok(str,";"))<58 && num>47)
                                C=atof(num);
                        }
                    }
                }
            }
        }
    }
    path=CaminoNuevo(Nombre,P,B,C);
    AddCamino(path,Origen,Dest,Mapa);
}*/

#endif // LISTAS_H_INCLUDED
