#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIMENSION 11
typedef struct nodo
{
    int dato;
    struct nodo *izq;
    struct nodo *dch;
}nodo;


typedef struct s_arbol
{
    nodo *raiz_arbol;
    nodo **arreglo_nodos;  //ARREGLO DE NODOS, PARA ALMACENAR LAS REFERENCIAS DE LOS NODOS CREADOS
    int num_nodos;
}s_arbol;


nodo* crearNodo(int dato);
void crearArbolBinario(s_arbol *arbol,int* array);
void imprimirArbol(nodo* n, int nivel);
void heapify(s_arbol *arbol);


int main(void)
{
    int i;
    //ARREGLO DE DATOS, DATOS DE ENTRADA
    int array[DIMENSION] = {3, 5, 8, 10, 17, 11, 13, 19, 22, 24, 29 };

    //DECLARAR E INICIARLIZAR VALORES DE LA VARIABLE TIPO S_ARBOL
    s_arbol arbol;
    arbol.raiz_arbol=NULL;
    arbol.arreglo_nodos=NULL;
    arbol.num_nodos=0;

    crearArbolBinario(&arbol,array);

    //IMPRIMIR EL ARREGLO DE NODOS DEL MONTON
    for(i=0;i<arbol.num_nodos;i++)
    {
        printf(" %d",arbol.arreglo_nodos[i]->dato);
    }
    printf("\n\n\r");

    imprimirArbol(arbol.raiz_arbol,0);
    printf("\n\n\r");
    //heapify(&arbol);

    printf("xd????");
    //IMPRIMIR EL Arbol ordenado por monton minimo
    //imprimirArbol(arbol.raiz_arbol,0);
    printf("\n\n\r");

    //BORRAR EL ARBOL, FREE A LOS NODOS
    for(i=arbol.num_nodos-1;i>=0;i--)
    {
        //LIBERAR NODO POR NODO
        free(arbol.arreglo_nodos[i]);
        arbol.num_nodos--;
    }
    //LIBERAR ESPACIO DONDE SE ALMACENABAN LAS REFERENCIAS DE LOS NODOS
    free(arbol.arreglo_nodos);
    //ACTUALIZAR APUNTADORES
    arbol.raiz_arbol=NULL;
    arbol.arreglo_nodos=NULL;

    return 0;
}

nodo* crearNodo(int dato)
{
    nodo *nuevo_nodo = malloc(sizeof(nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->dch = NULL;
    return nuevo_nodo;
}

void crearArbolBinario(s_arbol *arbol,int* array)
{
    nodo *nuevo_nodo;           //APUNTADOR DE NODO, PARA ALMACENAR LA REFERENCIA DEL NODO CREADO
    nodo **aux=NULL;            //APUNTADOR AUXILIAR PARA EL REALLOC

    int i;          //INDICE PARA ACCEDER AL LOS MIEMBROS DEL ARREGLO DE DATOS
    int num_nodos;  //CONTADOR DEL NUMERO DE NODOS CREADOS
    int longitud;   //DIMENSION DEL ARREGLO DE DATOS

    num_nodos=0;
    longitud=DIMENSION;

    //****************************************************************
    //CREAR EL ARREGLO DE NODOS
    for(i=0;i<longitud;i++)
    {
        nuevo_nodo = crearNodo(array[i]);   //CREAR NODO
        num_nodos++;                        //INCREMENTAR EL NUMERO DE NODOS
        if(arbol->arreglo_nodos==NULL)
        {
            arbol->arreglo_nodos = malloc(sizeof(nodo*)*num_nodos);    //ASIGNAR MEMORIA
            arbol->arreglo_nodos[num_nodos-1]=nuevo_nodo;              //ALMACENAR LA REFERENCIA DEL NUEVO NODO EN EL ARREGLO
        }
        else
        {
            aux=NULL;
            //INCREMENTAR EL ESPACIO EN MEMORIA PARA EL NUEVO NODO CREADO
            while(aux==NULL)
            {
                aux = realloc(arbol->arreglo_nodos,sizeof(nodo*)*num_nodos);   //REASIGNAR MEMORIA, INCREMENTAR
            }
            arbol->arreglo_nodos=aux;                      //ACTUALIZAR LA NUEVA REFERENCIA DEL LUGAR DE MEMORIA REASIGNADO CON LA NUEVA LONGITUD
            arbol->arreglo_nodos[num_nodos-1]=nuevo_nodo;  //ALMACENAR LA REFERENCIA DEL NUEVO NODO EN EL ARREGLO
        }
    }
    //****************************************************************
    //CREAR EL ARBOL BINARIO CON EL ARREGLO DE NODOS
    for(i=0;i<longitud;i++)
    {
        if(arbol->raiz_arbol==NULL)
        {
            arbol->raiz_arbol=arbol->arreglo_nodos[i]; //ASIGNAR LA PRIMERA POSICION DEL ARREGLO A LA RAIZ DEL ARBOL
            arbol->num_nodos++;
        }
        if(2*i+1<longitud)
        {
            arbol->arreglo_nodos[i]->izq = arbol->arreglo_nodos[2*i+1];   //ASIGNAR EL HIJO IZQUIERDO DEL NODO EN LA POSICION i DEL ARREGLO DE NODOS
            arbol->num_nodos++;
        }
        else
        {
            continue;
        }
        if(2*i+2<longitud)
        {
            arbol->arreglo_nodos[i]->dch = arbol->arreglo_nodos[2*i+2];   //ASIGNAR EL HIJO DERECHO DEL NODO EN LA POSICION i DEL ARREGLO DE NODOS
            arbol->num_nodos++;
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

void heapify(s_arbol *arbol)
{
    int num_nodos_padre;
    int i;
    nodo *aux, *aux_dch, *aux_izq;

    for(i=0;i<arbol->num_nodos;i++)
    {
        if(arbol->arreglo_nodos[i]->izq==NULL)
        {
            num_nodos_padre=i;
        }
    }

    //heap minimo
    for(i=num_nodos_padre-1;i>=0;i--)
    {
        if(arbol->arreglo_nodos[i]->dato > arbol->arreglo_nodos[2*i+2]->dato)
        {
            aux=arbol->arreglo_nodos[i];
            arbol->arreglo_nodos[i]=arbol->arreglo_nodos[2*i+2];
            arbol->arreglo_nodos[2*i+2]=aux;

            aux_dch =aux->dch;
            aux_izq =aux->izq;
            aux->dch = arbol->arreglo_nodos[i]->dch;
            aux->izq = arbol->arreglo_nodos[i]->izq;
            arbol->arreglo_nodos[i]->dch = (aux_dch == arbol->arreglo_nodos[i]) ? aux : aux_dch;
            arbol->arreglo_nodos[i]->izq = (aux_izq == arbol->arreglo_nodos[i]) ? aux : aux_izq;

            if(i!=0)
            {
                if(arbol->arreglo_nodos[(i-1)/2]->dch == aux)
                {
                    arbol->arreglo_nodos[(i-1)/2]->dch = arbol->arreglo_nodos[i];
                }
                else
                {
                    arbol->arreglo_nodos[(i-1)/2]->izq = arbol->arreglo_nodos[i];
                }
            }

            if (2*i+2<arbol->num_nodos)
            {
                if(arbol->arreglo_nodos[2*i+2]->izq!=NULL || arbol->arreglo_nodos[2*i+2]->dch!=NULL)
                {
                    i = (2*i+2)+1;
                    continue;
                }
            }
        }

        if(arbol->arreglo_nodos[i]->dato > arbol->arreglo_nodos[2*i+1]->dato)
        {
            aux=arbol->arreglo_nodos[i];
            arbol->arreglo_nodos[i]=arbol->arreglo_nodos[2*i+1];
            arbol->arreglo_nodos[2*i+1]=aux;

            aux_dch =aux->dch;
            aux_izq =aux->izq;
            aux->dch = arbol->arreglo_nodos[i]->dch;
            aux->izq = arbol->arreglo_nodos[i]->izq;
            arbol->arreglo_nodos[i]->dch = (aux_dch == arbol->arreglo_nodos[i]) ? aux : aux_dch;
            arbol->arreglo_nodos[i]->izq = (aux_izq == arbol->arreglo_nodos[i]) ? aux : aux_izq;

            if(i!=0)
            {
                if(arbol->arreglo_nodos[(i-1)/2]->dch == aux)
                {
                    arbol->arreglo_nodos[(i-1)/2]->dch = arbol->arreglo_nodos[i];
                }
                else
                {
                    arbol->arreglo_nodos[(i-1)/2]->izq = arbol->arreglo_nodos[i];
                }
            }
        }

        if(2*i+1<arbol->num_nodos)
        {
            if(arbol->arreglo_nodos[2*i+1]->izq!=NULL || arbol->arreglo_nodos[2*i+1]->dch!=NULL)
            {
                i = (2*i+1)+1;
            }
        }

        arbol->raiz_arbol=arbol->arreglo_nodos[0];
    }
}

