#ifndef BUSQUEDA_H_INCLUDED
#define BUSQUEDA_H_INCLUDED

void Yen(Lugares *origin, char Destino[], Camino *roads, float *suma_peso, int i, int num, char *name_road[]){
    char *name_road_2[100];
    float aux_peso;
    Lugares *spurNode= origin;
    Lugares *rootPath= origin;

    analizar_ruta(origin, Destino, roads, suma_peso, i, num, name_road);

    Camino *aux=roads;

    for(; aux; aux=roads->Next){
        if(strcmp(aux-> Name, name_road[0])== 0 && aux->Og->num_aristas > 1){
            aux_peso= aux->Peso[i];
            aux-> Peso[i]= 0;
        }
    }

    analizar_ruta(origin, Destino, roads, suma_peso, i, num, name_road_2);

    aux-> Peso[i]= aux_peso;
}

void analizar_ruta(Lugares *pos_actual, char Destino[], Camino *roads, float *suma_peso, int i, int num, char *name_road[]){
    if(strcmp(pos_actual-> Name, Destino)== 0){
        return;
    }

    Camino *aux_roads= roads;

    for(; aux_roads; aux_roads= aux_roads->Next){
        if(strcmp(aux_roads->Og->Name, pos_actual->Name)== 0 && aux_roads->Peso[i]!=0 && suma_peso[i]<suma_peso[i]+aux_roads->Peso[i]){
                suma_peso[i]+= aux_roads->Peso[i];
                strcpy(name_road[num], aux_roads-> Name);
                pos_actual= aux_roads-> Ady;
        }
    }
    num++;
    analizar_ruta(pos_actual, Destino, roads, suma_peso, i, num, name_road);
}

void BuscarRutaOptima(Camino *path,char Origen[], char Destino[]){
    int i=1, flag=1;
    int num=0;
    float peso_final[3];
    char *name_road[100];
    Camino *aux= path;
    Lugares *origin;

    while(flag==1){
        if(strcmp(aux->Og->Name, Origen)== 0){
            flag=0;
            origin= aux->Og;
        } else{
            aux= aux->Next;
        }
    }

    for(int i=0; i<3; i++){
            peso_final[i]=0;
            Yen(origin, Destino, path, peso_final, i, num, name_road);
    }

    for(int i=0; i<3; i++)
        printf("%f\n", peso_final[i]);

}

#endif // BUSQUEDA_H_INCLUDED
