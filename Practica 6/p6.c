//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 6
//TEMA: ARBOLES BINARIOS Y ARBOLES BINARIOS DE EXPRESION
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoArbol {
    char valor;
    struct NodoArbol *izquierda, *derecha;
} NodoArbol;

typedef struct {
    NodoArbol **elementos;
    int tope;
} Pila;

void inicializarPila(Pila *p) {
    p->elementos = malloc(100 * sizeof(NodoArbol*));
    p->tope = -1;
}

void apilar(Pila *p, NodoArbol *nodo) {
    p->elementos[++p->tope] = nodo;
}

NodoArbol *desapilar(Pila *p) {
    return p->elementos[p->tope--];
}

int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedencia(char operador) {
    if (operador == '+' || operador == '-') return 1;
    if (operador == '*' || operador == '/') return 2;
    return 0;
}

NodoArbol *crearNodo(char valor) {
    NodoArbol *nuevo = malloc(sizeof(NodoArbol));
    nuevo->valor = valor;
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

NodoArbol *construirArbol(char *expresion) {
    Pila operadores;
    inicializarPila(&operadores);
    Pila operandos;
    inicializarPila(&operandos);

    for (int i = 0; i < strlen(expresion); i++) {
        if (expresion[i] == ' ') continue;

        if (esOperador(expresion[i])) {
            while (operadores.tope != -1 && 
                   precedencia(operadores.elementos[operadores.tope]->valor) >= precedencia(expresion[i])) {
                NodoArbol *op = desapilar(&operadores);
                op->derecha = desapilar(&operandos);
                op->izquierda = desapilar(&operandos);
                apilar(&operandos, op);
            }
            apilar(&operadores, crearNodo(expresion[i]));
        } else {
            apilar(&operandos, crearNodo(expresion[i]));
        }
    }

    while (operadores.tope != -1) {
        NodoArbol *op = desapilar(&operadores);
        op->derecha = desapilar(&operandos);
        op->izquierda = desapilar(&operandos);
        apilar(&operandos, op);
    }

    return desapilar(&operandos);
}

void imprimirArbol(NodoArbol *nodo, int nivel) {
    if (nodo != NULL) {
        // Imprimir el nodo actual
        printf(" %c", nodo->valor);

        // Procesar el nodo derecho
        if (nodo->derecha != NULL) {
            printf("\n");
            for (int i = 0; i < nivel + 1; i++) {
                if (i == nivel) {
                    printf(" |____R ");
                } else {
                    printf(" |      ");
                }
            }
            imprimirArbol(nodo->derecha, nivel + 1);
        }

        // Procesar el nodo izquierdo
        if (nodo->izquierda != NULL) {
            printf("\n");
            for (int i = 0; i < nivel + 1; i++) {
                printf(" |      ");
            }
            printf("\n");
            for (int i = 0; i < nivel + 1; i++) {
                if (i == nivel) {
                    printf(" |____L ");
                } else {
                    printf(" |      ");
                }
            }
            imprimirArbol(nodo->izquierda, nivel + 1);
        }
    }
}


int main() {
    char expresion[] = "X*Y/A+B*C";
    NodoArbol *raiz = construirArbol(expresion);
    imprimirArbol(raiz, 0);
    return 0;
}
