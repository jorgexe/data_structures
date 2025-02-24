#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIMENSION 11

typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *dch;
} nodo;

typedef struct s_arbol {
    nodo *raiz_arbol;
    nodo **arreglo_nodos;  // ARREGLO DE NODOS, PARA ALMACENAR LAS REFERENCIAS DE LOS NODOS CREADOS
    int num_nodos;
} s_arbol;

nodo* crearNodo(int dato);
void crearArbolBinario(s_arbol *arbol,int* array);
void imprimirArbol(nodo* n, int nivel);
void heapify(s_arbol *arbol);

int main(void) {
    int array[DIMENSION] = {3, 5, 8, 10, 17, 11, 13, 19, 22, 24, 29};
    s_arbol arbol;
    arbol.raiz_arbol = NULL;
    arbol.arreglo_nodos = NULL;
    arbol.num_nodos = 0;

    crearArbolBinario(&arbol, array);
    
    //imprimr arbol sin heapify
    imprimirArbol(arbol.raiz_arbol, 0);
    printf("\n\n\n ***************\n");


    heapify(&arbol);

    //imprimir arbol con heapify
    imprimirArbol(arbol.raiz_arbol, 0);
    printf("\n");

    // Liberar recursos
    for(int i = arbol.num_nodos - 1; i >= 0; i--) {
        free(arbol.arreglo_nodos[i]);
    }
    free(arbol.arreglo_nodos);

    return 0;
}

nodo* crearNodo(int dato) {
    nodo *nuevo_nodo = malloc(sizeof(nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->dch = NULL;
    return nuevo_nodo;
}

void crearArbolBinario(s_arbol *arbol, int* array) {
    int i;
    for(i = 0; i < DIMENSION; i++) {
        nodo *nuevo_nodo = crearNodo(array[i]);
        if(arbol->arreglo_nodos == NULL) {
            arbol->arreglo_nodos = malloc(sizeof(nodo*) * (i + 1));
        } else {
            arbol->arreglo_nodos = realloc(arbol->arreglo_nodos, sizeof(nodo*) * (i + 1));
        }
        arbol->arreglo_nodos[i] = nuevo_nodo;
        arbol->num_nodos++;
    }

    for(i = 0; i < DIMENSION; i++) {
        if(i == 0) {
            arbol->raiz_arbol = arbol->arreglo_nodos[i];
        }
        if(2 * i + 1 < DIMENSION) {
            arbol->arreglo_nodos[i]->izq = arbol->arreglo_nodos[2 * i + 1];
        }
        if(2 * i + 2 < DIMENSION) {
            arbol->arreglo_nodos[i]->dch = arbol->arreglo_nodos[2 * i + 2];
        }
    }
}

void imprimirArbol(nodo* n, int nivel)
{
    int i;
    if (n != NULL)
        {
        printf(" %d", n->dato);
        if(n->dch!=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimirArbol(n->dch, nivel + 1);
        }
        if(n->izq!=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimirArbol(n->izq, nivel + 1);
        }
    }
}

void heapify(s_arbol *arbol) {
    int i, j, num_nodos_padre = (arbol->num_nodos - 2) / 2;
    nodo *temp;

    for(i = num_nodos_padre; i >= 0; i--) {
        for(j = i; j * 2 + 1 < arbol->num_nodos; ) {
            int hijo = j * 2 + 1;
            if(hijo + 1 < arbol->num_nodos && arbol->arreglo_nodos[hijo + 1]->dato < arbol->arreglo_nodos[hijo]->dato) {
                hijo++;
            }
            if(arbol->arreglo_nodos[j]->dato <= arbol->arreglo_nodos[hijo]->dato) {
                break;
            }
            temp = arbol->arreglo_nodos[j];
            arbol->arreglo_nodos[j] = arbol->arreglo_nodos[hijo];
            arbol->arreglo_nodos[hijo] = temp;
            j = hijo;
        }
    }
}


