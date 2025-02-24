#ifndef NODOS_H
#define NODOS_H

#include <stdlib.h>
#include <stdio.h>

#define FINAL -1
#define INICIO 0
#define INICIO_FINAL 1
#define FINAL_INICIO -1

//char string_NULL[] = "NULL    \0";
typedef struct cancion
{
    char nombre[30];
    char artista_grupo[20];
}Cancion;

typedef struct nodo
{
    int dato;
    Cancion song;
    struct nodo *anterior;
    struct nodo *siguiente;
}Nodo;

typedef struct lista_2E
{
    Nodo *inicio;
    Nodo *fin;
    int num_nodos;
}LISTA_2E;

//PROTOTIPO DE FUNCION PARA AGREGAR NODOS EN UNA LISTA
int agregar_nodo(LISTA_2E *lista,Cancion song,int posicion);
//PROTOTIPO DE FUNCION PARA ELIMINAR UN NODO DE UNA LISTA
int eliminar_nodo(LISTA_2E *lista,int posicion);
//PROTOTIPO DE FUNCION PARA CREAR NODOS
void crear_Nodo(Nodo **nodo,Cancion song);
//PROTOTIPO DE FUNCION PARA DESPLEGAR LOS NODOS DE UNA LISTA
void recorrer_nodos(LISTA_2E param_lista,int direccion);
void print_Nodo(Nodo *p_nodo,int index);

void display_circular(LISTA_2E param_lista);

void display_canciones(Cancion *songs,int length,int y);


#endif