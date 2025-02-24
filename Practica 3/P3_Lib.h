#ifndef P3_LIB_H
#define P3_LIB_H

#include <stdio.h>
#include <stdlib.h>

#define SIN_LIMITE 0

typedef struct book
{
    char *nombre;
    char *genero;
    int release_date;
}Book;

typedef struct elemento
{
    Book *libro;
    struct elemento *siguiente;
} Elemento;

typedef struct pila
{
    Elemento *cima;
    int longitud;
    int num_elementos;
} Pila_LE;

typedef struct g_p
{
    Pila_LE *pilas;
    int num_pilas;
} Grupo_Pila;

void get_pila_of_books(Pila_LE *p_books);
///---------------------
void iniciarlizar_pila(Pila_LE *pila,int longitud);
int llena(Pila_LE p);
int vacia(Pila_LE p);
void insertar(Pila_LE *p,Book *libro);
Book *mover(Pila_LE *p);
void quitar(Pila_LE *p);
///---------------------

#endif