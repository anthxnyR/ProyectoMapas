#ifndef BUSQUEDA_H_INCLUDED
#define BUSQUEDA_H_INCLUDED

#define MINIMO 10000

Lugares *comparar_ruta(Lugares *p_lug, Camino *p_cam, int i){
    for(; p_cam; p_cam= p_cam->Next){
        if(strcmp(p_lug->Name, p_cam->Og->Name)==0 && p_cam->Ady->status==0){
            if(p_lug->suma_peso+p_cam->Peso[i] < p_cam->Ady->suma_peso){
                p_cam->Ady->ruta_og= p_cam;
                p_cam->Ady->suma_peso= p_lug->suma_peso + p_cam->Peso[i];
            }
        }
    }
    return p_lug;
}

float ruta_minima(Lugares *p_lug, float minimo){
    minimo= MINIMO;

    for(; p_lug; p_lug= p_lug->Next){
        if(p_lug->status==0 && p_lug->suma_peso<minimo){
            minimo= p_lug->suma_peso;
        }
    }
    return minimo;
}

Lugares *next_place(Lugares *p_lug, float minimo){
    minimo= MINIMO;
    Lugares *next_lug=(Lugares *)malloc(sizeof(Lugares));

    for(; p_lug; p_lug= p_lug->Next){
        if(p_lug->status==0 && p_lug->suma_peso<minimo){
            next_lug= p_lug;
        }
    }
    return next_lug;
}

int analizar(Lugares *pos_actual, Camino *p_cam){
    for(; p_cam; p_cam=p_cam->Next){
        if(strcmp(p_cam->Og->Name, pos_actual->Name)==0)
            return 1;
    }
    return 0;
}

void BuscarRutaOptima(Camino *path, Lugares *vertices, char Origen[], char Destino[]){
    int flag=1, aux_int;
    int medio=0;
    float minimo=0, aux_float;
    char *ruta_final[100];
    Camino *aux=path;
    Lugares *pos_actual, *origin;

    while(flag==1){
        if(strcmp(aux->Og->Name, Origen)== 0){
            flag=0;
            pos_actual= aux->Og;
            origin= aux->Og;
        } else{
            aux= aux->Next;
        }
    }
    aux= path;
    pos_actual->suma_peso=0;
    pos_actual->status= 1;
    while(pos_actual->Name != Destino){
        aux= comparar_ruta(pos_actual, path, medio);
        aux_float= ruta_minima(vertices, minimo);
        pos_actual= next_place(vertices, minimo);
        pos_actual->suma_peso= aux_float;
        pos_actual->status= 1;
        if(analizar(pos_actual, path) == 0 && pos_actual->Name != Destino)
            pos_actual= pos_actual->ruta_og->Og;
    }

    printf("%f \n", pos_actual->suma_peso);
    int i=0;
    while(pos_actual->Name != origin->Name){
        ruta_final[i++]=pos_actual->Name;
        pos_actual= pos_actual->ruta_og->Og;
    }

    for(int j=i; j>-1; j--)
        printf("%c \n", ruta_final[j]);
}

/*
void Yen(Lugares *origin, char Destino[], Camino *roads, float suma_peso[3][2], int *i, int *j, char *name_road[]){
    //char *name_road_2[100];
    float aux_peso;
    Lugares *rootPath;

    analizar_ruta(origin, Destino, roads, suma_peso, i, j, name_road);

    Camino *aux=roads;

    for(; aux; aux=roads->Next){
        if(strcmp(aux-> Name, name_road[0])== 0 && aux->Og->num_aristas > 1){
            aux_peso= aux->Peso[*i];
            aux-> Peso[*i]= 0;
            rootPath= aux->Og;
        }
    }

    analizar_ruta(rootPath, Destino, roads, suma_peso, i, j, name_road);

    aux-> Peso[*i]= aux_peso;
}

void analizar_ruta(Lugares *pos_actual, char Destino[], Camino *roads, float suma_peso[3][2], int *i, int *j, char *name_road[]){
    if(strcmp(pos_actual->Name, Destino)== 0){
        return;
    }

    Camino *aux_roads= roads;
    float aux_peso=0;

    for(; aux_roads; aux_roads= aux_roads->Next){
        if(strcmp(aux_roads->Og->Name, pos_actual->Name)== 0 && aux_roads->Peso[*i]!=0 && aux_peso<suma_peso[*i][*j]+aux_roads->Peso[*i]){
                aux_peso= aux_roads->Peso[*i];
                strcpy(name_road, aux_roads->Name);
                pos_actual= aux_roads-> Ady;
        }
    }
    suma_peso[*i][*j]+= aux_peso;
    analizar_ruta(pos_actual, Destino, roads, suma_peso, i, j, name_road);
}

void BuscarRutaOptima(Camino *path,char Origen[], char Destino[]){
    //int *i=0, *j=0;
    int k=0;
    int *num=0, flag=1;
    float peso_final[3][2];
    char *name_road[20];
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
        for(int j=0; j<2; j++){
            peso_final[i][j]=0;
            Yen(origin, Destino, path, peso_final, &i, &j, name_road);
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            printf("%f\n", peso_final[i][j]);
        }
    }
}
*/

#endif // BUSQUEDA_H_INCLUDED
