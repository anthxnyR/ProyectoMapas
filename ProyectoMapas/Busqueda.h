#ifndef BUSQUEDA_H_INCLUDED
#define BUSQUEDA_H_INCLUDED

void analizar_ruta(Lugares *pos_actual, char Destino[], Camino *roads, float suma_peso[], int *i, int num){
    if(strcmp(pos_actual-> Name, Destino)== 0)
        return;

    int peso=0;
    Camino *aux_roads= roads;

    for(; aux_roads; aux_roads= aux_roads->Next){
        if(strcmp(aux_roads->Og->Name, pos_actual->Name)== 0 && aux_roads->Peso[*i]!=0 && peso<suma_peso[*i]+aux_roads->Peso[*i]){
            peso= aux_roads->Peso[*i];
            strcopy(name_road[num], aux_roads-> Name);
            pos_actual= aux_roads-> Ady;
        }
    }
    suma_peso[*i]+= peso;

    analizar_ruta(pos_actual, Destino, roads, suma_peso, i, num+1);
}

void BuscarRutaOptima(Camino *path,char Origen[50], char Destino[50]){
    int i=1, flag=1, num=0;
    float peso_final[3];
    char *name_road[100];
    Lugares *origin;
    
    while(flag=1){
        if(strcmp(origin->Name, Origen)== 0){
            flag=0;
        } else{
            origin= origin->Next;
        } 
    }

    for(int i=0; i<3; i++){
        int peso_final[i]=0;
        analizar_ruta(origin, Destino, path, peso_final, &i, num);
    }
}

#endif // BUSQUEDA_H_INCLUDED