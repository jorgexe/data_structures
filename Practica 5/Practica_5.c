//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 5
//TEMA: ARBOLES BINARIOS
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERDADERO 1
#define FALSO 0

typedef struct s_nodo
{
    int valor;
    struct s_nodo* izquierda;
    struct s_nodo* derecha;
}Nodo;

Nodo* crearNodo(int valor);
Nodo* borraArbol(Nodo** nodo);
void imprimirArbol(Nodo* nodo, int nivel);
void captura_int(int *n);
//IMPLEMENTAR
void insertar_nodo(Nodo **arbol, int numero);
int calcular_nivel(Nodo *arbol,int num);
int num_elementos(Nodo* arbol);
int calcular_profundidad(Nodo *arbol);

int main(void)
{
    int opcion;
    int corre_programa=VERDADERO;
    Nodo* raiz = NULL;


    while(corre_programa)
    {
        system("cls");
        //MENU
        printf("1. Insertar nodo en el arbol\n");
        printf("2. Obtener numero de nodos en el arbol\n");
        printf("3. Calcular profundidad/altura del arbol\n");
        printf("4. Imprimir arbol\n");
        printf("5. Calcular nivel de nodo\n");
        printf("6. Terminar programa\n\n");
        
        printf("\n\n\r Escoge opcion: ");
        captura_int(&opcion);


        fflush(stdin);
        system("cls");
        switch(opcion)
        {
            case 1:
            {
                //INSERTAR NODO EN EL ARBOL
                int numero;
                printf("Introduce el número a insertar: ");
                captura_int(&numero);
                insertar_nodo(&raiz, numero);
                break;
            }
            case 2:
            {
                //OBTENER NUMERO DE NODOS EN EL ARBOL
                int numNodos = num_elementos(raiz);
                printf("Número de nodos en el árbol: %d\n", numNodos);
                break;
            }
            case 3:
            {
                //CALCULAR PROFUNDIDAD/ALTURA DEL ARBOL
                int profundidad = calcular_profundidad(raiz);
                printf("Profundidad del árbol: %d\n", profundidad);
                break;
            }
            case 4:
            {
                //IMPRIMIR ARBOL
                imprimirArbol(raiz, 0);
                break;
            }
            case 5:
            {
                //CALCULAR NIVEL DE NODO
                int num;
                printf("Introduce el número a buscar: ");
                captura_int(&num);
                int nivel = calcular_nivel(raiz, num);
                if (nivel >= 0) {
                    printf("Nivel del nodo con valor %d: %d\n", num, nivel);
                } else {
                    printf("El nodo con valor %d no se encuentra en el árbol.\n", num);
                }
                break;
            }
            case 6:
            {
                //TERMINAR PROGRAMA
                borraArbol(&raiz);
                corre_programa=FALSO;
                break;
            }
            default:
                break;
        }
    }


    printf("\n\n");
    return 0;
}

Nodo* crearNodo(int valor)
{
    Nodo* nodo = ( Nodo*)malloc(sizeof( Nodo));
    nodo->valor = valor;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

void imprimirArbol(Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf(" %d", nodo->valor);
        if(nodo->derecha!=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimirArbol(nodo->derecha, nivel + 1);
        }
        if(nodo->izquierda!=NULL)
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
            imprimirArbol(nodo->izquierda, nivel + 1);
        }
    }
}

Nodo* borraArbol(Nodo** arbol)
{
    if ((*arbol) != NULL)
    {
        if((*arbol)->derecha!=NULL)
        {
            (*arbol)->derecha = borraArbol(&(*arbol)->derecha);
        }
        if((*arbol)->izquierda!=NULL)
        {
            (*arbol)->izquierda = borraArbol(&(*arbol)->izquierda);
        }
        free((*arbol));
        return NULL;

    }
}

void captura_int(int *n)
{
    char *end;
    char buf[64];
    do
    {
        if (!fgets(buf, sizeof buf, stdin))
            break;
        // remove \n
        buf[strlen(buf) - 1] = 0;
        *n = strtol(buf, &end, 10);
    }while (end != buf + strlen(buf));
}

void insertar_nodo(Nodo **arbol, int numero)
{
    if (*arbol == NULL) {
        *arbol = crearNodo(numero);
    } else {
        if (numero < (*arbol)->valor || numero == (*arbol)->valor) {
            insertar_nodo(&((*arbol)->izquierda), numero);
        } else {
            insertar_nodo(&((*arbol)->derecha), numero);
        }
    }
}

int calcular_nivel(Nodo *arbol, int num)
{
    if (arbol == NULL) {
        return -1;
    }

    if (num == arbol->valor) {
        return 0;
    } else if (num < arbol->valor) {
        int nivel_izquierda = calcular_nivel(arbol->izquierda, num);
        if (nivel_izquierda >= 0) {
            return 1 + nivel_izquierda;
        }
    } else {
        int nivel_derecha = calcular_nivel(arbol->derecha, num);
        if (nivel_derecha >= 0) {
            return 1 + nivel_derecha;
        }
    }

    return -1;
}

int num_elementos(Nodo* arbol)
{
    if (arbol == NULL) {
        return 0;
    }
    return 1 + num_elementos(arbol->izquierda) + num_elementos(arbol->derecha);
}

int calcular_profundidad(Nodo *arbol)
{
    if (arbol == NULL) {
        return 0;
    }

    int profundidad_izquierda = calcular_profundidad(arbol->izquierda);
    int profundidad_derecha = calcular_profundidad(arbol->derecha);

    return 1 + (profundidad_izquierda > profundidad_derecha ? profundidad_izquierda : profundidad_derecha);
}
