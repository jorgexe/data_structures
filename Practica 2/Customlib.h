#ifndef CUSTOMLIB_H
#define CUSTOMLIB_H

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE 64
#define ARRAY_SIZE 64
#define CANTIDAD_OPCIONES 9

typedef struct cadenas
{
    char cadena[ARRAY_SIZE];
}Cadenas;



void gotoxy(int x,int y);
int wherex();
int wherey();
void captura_cadena(int p_min_size,char *string_indicacion,char **cadena,int *p_size);
void captura_int(int p_min,int p_max,char *string_indicacion,int *p_entero);
void esperar_enter(void);
void display_options(Cadenas *opciones);
#endif