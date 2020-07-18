#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct Lugares{
    char Name[100];
    int num;
    struct Lugares *Next;
    struct Camino *Ady;
}

typedef struct Camino{
    char Name[100];
    float Peso[3];
    int num;
    struct Camino *Next;
    struct Lugares *Ady, *Og;
}

struct Route{
    struct Camino *path;
    struct Route *next;
}

#endif // LISTAS_H_INCLUDED
