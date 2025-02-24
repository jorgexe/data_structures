//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 7
//TEMA: ARBOLES BINARIOS Y MONTONES (HEAPS)
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

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
void heapify(s_arbol *arbol, int n, int i);
void construirHeapMinimo(s_arbol *arbol);
void reconstruirArbolBinario(s_arbol *arbol);
void eliminarDeHeap(s_arbol *arbol, int dato);
void insertarEnHeap(s_arbol *arbol, int nuevoDato);

int main(void) {
    s_arbol arbol;
    arbol.raiz_arbol = NULL;
    arbol.arreglo_nodos = NULL;
    arbol.num_nodos = 0;

    int opcion, dato, i;
    // ARREGLO DE DATOS, DATOS DE ENTRADA
    int array[DIMENSION] = {29, 24, 22, 19, 13, 11, 17, 10, 8, 5, 3};

    //Imprimir árbol binario inicial
    printf("Árbol binario inicial:\n");
    crearArbolBinario(&arbol, array);
    imprimirArbol(arbol.raiz_arbol, 0);
    printf("\n\n");

    // hacer heapify
    construirHeapMinimo(&arbol);
    reconstruirArbolBinario(&arbol);
    printf("Árbol binario convertido en heap mínimo.\n\n");
    imprimirArbol(arbol.raiz_arbol, 0);
    printf("\n*******************************\n");

    while (1) {
        printf("Menú:\n");
        printf("1. Insertar un nuevo dato en el heap.\n");
        printf("2. Eliminar un dato en el heap.\n");
        printf("3. Mostrar heap.\n");
        printf("4. Salir.\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el dato para insertar en el heap: ");
                scanf("%d", &dato);
                insertarEnHeap(&arbol, dato);
                printf("Dato insertado en el heap.\n");
                break;

            case 2:
                printf("Ingrese el dato para eliminar del heap: ");
                scanf("%d", &dato);
                eliminarDeHeap(&arbol, dato);
                printf("Dato eliminado del heap.\n");
                break;

            case 3:
                printf("Impresión del heap:\n");
                imprimirArbol(arbol.raiz_arbol, 0);
                printf("\n");
                break;

            case 4:
                printf("Saliendo...\n");
                // Liberar memoria antes de salir
                for (i = arbol.num_nodos - 1; i >= 0; i--) {
                    free(arbol.arreglo_nodos[i]);
                }
                free(arbol.arreglo_nodos);
                return 0;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }
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

void heapify(s_arbol *arbol, int n, int i) {
    int minimo = i; // Inicializar el mínimo como raíz
    int izq = 2 * i + 1; // índice del hijo izquierdo
    int dch = 2 * i + 2; // índice del hijo derecho

    // Si el hijo izquierdo existe y es menor que el mínimo actual, actualizar el mínimo
    if (izq < n && arbol->arreglo_nodos[izq]->dato < arbol->arreglo_nodos[minimo]->dato) {
        minimo = izq;
    }

    // Si el hijo derecho existe y es menor que el nuevo mínimo, actualizar el mínimo
    if (dch < n && arbol->arreglo_nodos[dch]->dato < arbol->arreglo_nodos[minimo]->dato) {
        minimo = dch;
    }

    // Si el mínimo no es la raíz, intercambiar y continuar heapify
    if (minimo != i) {
        nodo *temp = arbol->arreglo_nodos[i];
        arbol->arreglo_nodos[i] = arbol->arreglo_nodos[minimo];
        arbol->arreglo_nodos[minimo] = temp;
        heapify(arbol, n, minimo);
    }
}

void construirHeapMinimo(s_arbol *arbol) {
    int n = arbol->num_nodos;
    // Construir heap (reordenar arreglo)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arbol, n, i);
    }
}

void reconstruirArbolBinario(s_arbol *arbol) {
    int i;
    int n = arbol->num_nodos;

    // Reconstruir los enlaces del árbol binario según el arreglo de nodos reordenado
    for(i = 0; i < n; i++) {
        if (2 * i + 1 < n) {
            arbol->arreglo_nodos[i]->izq = arbol->arreglo_nodos[2 * i + 1];
        } else {
            arbol->arreglo_nodos[i]->izq = NULL;
        }

        if (2 * i + 2 < n) {
            arbol->arreglo_nodos[i]->dch = arbol->arreglo_nodos[2 * i + 2];
        } else {
            arbol->arreglo_nodos[i]->dch = NULL;
        }
    }

    // Actualizar la raíz del árbol
    if (n > 0) {
        arbol->raiz_arbol = arbol->arreglo_nodos[0];
    }
}

void insertarEnHeap(s_arbol *arbol, int nuevoDato) 
{
    nodo *nuevo_nodo = crearNodo(nuevoDato); // Crear un nuevo nodo con el dato
    nodo **aux = NULL;                       // Apuntador auxiliar para realloc

    // Incrementar el espacio en memoria para el nuevo nodo
    aux = realloc(arbol->arreglo_nodos, sizeof(nodo*) * (arbol->num_nodos + 1));
    if (!aux) {
        printf("Error al asignar memoria\n");
        return;
    }

    arbol->arreglo_nodos = aux;
    arbol->arreglo_nodos[arbol->num_nodos] = nuevo_nodo; // Insertar el nuevo nodo al final del arreglo
    arbol->num_nodos++;

    // Flotar el nuevo nodo hacia arriba para mantener la propiedad de montón mínimo
    int i = arbol->num_nodos - 1;
    while (i != 0 && arbol->arreglo_nodos[(i - 1) / 2]->dato > arbol->arreglo_nodos[i]->dato) {
        // Intercambiar con el nodo padre
        nodo *temp = arbol->arreglo_nodos[(i - 1) / 2];
        arbol->arreglo_nodos[(i - 1) / 2] = arbol->arreglo_nodos[i];
        arbol->arreglo_nodos[i] = temp;
        i = (i - 1) / 2;
    }

    // Reconstruir el árbol binario con el arreglo de nodos actualizado
    reconstruirArbolBinario(arbol);
}

void eliminarDeHeap(s_arbol *arbol, int dato) 
{
    int i;
    for (i = 0; i < arbol->num_nodos; i++) {
        if (arbol->arreglo_nodos[i]->dato == dato) {
            break;
        }
    }

    if (i == arbol->num_nodos) {
        printf("Dato no encontrado en el heap\n");
        return;
    }

    // Reemplazar el nodo a eliminar con el último nodo
    nodo *ultimoNodo = arbol->arreglo_nodos[arbol->num_nodos - 1];
    arbol->arreglo_nodos[i] = ultimoNodo;
    arbol->num_nodos--;

    // Hundir el nodo reemplazado para mantener la propiedad de montón mínimo
    while ((2 * i + 1) < arbol->num_nodos) {
        int minimo = i;
        int izq = 2 * i + 1;
        int dch = 2 * i + 2;

        if (izq < arbol->num_nodos && arbol->arreglo_nodos[izq]->dato < arbol->arreglo_nodos[minimo]->dato) {
            minimo = izq;
        }

        if (dch < arbol->num_nodos && arbol->arreglo_nodos[dch]->dato < arbol->arreglo_nodos[minimo]->dato) {
            minimo = dch;
        }

        if (minimo != i) {
            nodo *temp = arbol->arreglo_nodos[i];
            arbol->arreglo_nodos[i] = arbol->arreglo_nodos[minimo];
            arbol->arreglo_nodos[minimo] = temp;
            i = minimo;
        } else {
            break;
        }
    }

    // Reconstruir el árbol binario con el arreglo de nodos actualizado
    reconstruirArbolBinario(arbol);
}

