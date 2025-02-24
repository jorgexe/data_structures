//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 3
//TEMA: PILAS
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P3_Lib.h"

#define SIN_LIMITE 0
#define VERDADERO 1
#define FALSO 0

void mostrar_menu(void);

void imprimir_pila(Pila_LE p);
void capture_int(int *n);

//IMPLEMENTAR
void apilar_generos(Grupo_Pila *grupo,Book *libro);
void apilar_fecha(Grupo_Pila *grupo,Book *libro);

int main(void)
{
    int i;
    int option;
    int corre_programa=VERDADERO;
    Book *libro;
    Pila_LE caja_libros;
    get_pila_of_books(&caja_libros);


    Grupo_Pila opciones[3];
    for(i=0;i<3;i++)
    {
        opciones[i].pilas = (Pila_LE *) malloc(sizeof(Pila_LE));
        opciones[i].num_pilas = 0;
        iniciarlizar_pila(opciones[i].pilas,SIN_LIMITE);
    }

    while(corre_programa)
    {
        system("cls");
        mostrar_menu();
        printf("\n\n\r Escoge opcion: ");
        capture_int(&option);


        fflush(stdin);
        system("cls");
        switch(option)
        {
            case 1:
                    printf("\n\r [1] APILAR TODO");
                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        opciones[0].num_pilas=1;
                        while(!vacia(caja_libros))
                        {
                            insertar(opciones[0].pilas,mover(&caja_libros));
                        }
                    }
                    imprimir_pila(*opciones[0].pilas);
                    printf("\n\n\r");
                    system("pause");
                    break;
            case 2:
                    printf("\n\r [2] APILAR POR GENERO");
                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        while(!vacia(caja_libros))
                        {
                            libro = mover(&caja_libros);
                            apilar_generos(&opciones[1],libro);
                        }
                    }

                    if (opciones[1].num_pilas>0)
                    {
                        printf("\n\n\r");
                        printf("\n\r Generos:");
                        for(i=0;i<opciones[1].num_pilas;i++)
                        {
                            printf("\n\r [%d] %s",i,opciones[1].pilas[i].cima->libro->genero);
                        }
                        printf("\n\n\r Escoge opcion: ");
                        capture_int(&option);
                        if(option>=0 && option<opciones[1].num_pilas)
                        {
                            imprimir_pila(*((opciones[1].pilas)+option));
                        }
                        printf("\n\n\r");
                        system("pause");
                    }
                    break;
            case 3:
                    printf("\n\r [3] APILAR POR FECHA");

                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        while(!vacia(caja_libros))
                        {
                            libro = mover(&caja_libros);
                            apilar_fecha(&opciones[2],libro);
                        }
                    }

                    if (opciones[2].num_pilas>0)
                    {
                        printf("\n\n\r");
                        for(i=0;i<opciones[2].num_pilas;i++)
                        {
                            printf("\n\r [%d] %d",i,opciones[2].pilas[i].cima->libro->release_date);
                        }
                        printf("\n\n\r Escoge opcion: ");
                        capture_int(&option);
                        if(option>=0 && option<opciones[2].num_pilas)
                        {
                            imprimir_pila(*((opciones[2].pilas)+option));
                        }
                        printf("\n\n\r");
                        system("pause");
                    }
                    break;
            case 4:
                    printf("\n\r [4] SALIR");
                    corre_programa=FALSO;
                    printf("\n\n\r");
                    system("pause");
                    break;
            default:
                    break;
        }
    }

    printf("\n\n\r");
    return 0;
}

void capture_int(int *n)
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

void apilar_generos(Grupo_Pila *grupo,Book *libro)
{
    int i;
    if(grupo->num_pilas==0)
    {
        //INSERTAR SI NO EXISTE NINGUNA PILA, APENAS SE ACOMODARAN LOS LIBROS
        grupo->num_pilas++;
        Pila_LE *p=NULL;
        while(p==NULL)
        {
            p = (Pila_LE *) realloc(grupo->pilas,sizeof(Pila_LE)*(grupo->num_pilas));
        }
        grupo->pilas = p;
        iniciarlizar_pila(&grupo->pilas[(grupo->num_pilas)-1],SIN_LIMITE);
        insertar(&grupo->pilas[(grupo->num_pilas)-1],libro);
    }
    else
    {
        //BUSCAR SI LA PILA YA EXISTE E INSERTAR
        for(i=0;i<grupo->num_pilas;i++)
        {
            if(0==strcmp((grupo->pilas+i)->cima->libro->genero,libro->genero))
            {
                insertar(&grupo->pilas[i],libro);
                return;
            }
        }
        //-------------------------------------------------
        //SI NO EXISTE LA PILA CREARLA
        //IMPLEMENTAR CREAR NUEVA PILA E INSERTAR
        //INCREMENTAR NUM PILAS
        grupo->num_pilas++;
        //ASIGNAR ESPACIO PARA LA NUEVA PILA (REALLOC)
        Pila_LE *p = (Pila_LE *)realloc(grupo->pilas, sizeof(Pila_LE) * grupo->num_pilas);
        if (p == NULL)
        {
            fprintf(stderr, "Error al asignar memoria para la nueva pila.\n");
            exit(EXIT_FAILURE);
        }
        grupo->pilas = p;
        //INICIALIZAR PILA
        iniciarlizar_pila(&grupo->pilas[(grupo->num_pilas) - 1], SIN_LIMITE);
        //INSERTAR LIBRO
        insertar(&grupo->pilas[(grupo->num_pilas) - 1], libro);
    }
}


void apilar_fecha(Grupo_Pila *grupo, Book *libro)
{
    int i;
    // Si no hay ninguna pila en el grupo, crear una nueva pila y apilar el libro
    if (grupo->num_pilas == 0)
    {
        grupo->num_pilas++;
        Pila_LE *p = (Pila_LE *)malloc(sizeof(Pila_LE));
        iniciarlizar_pila(p, SIN_LIMITE);
        insertar(p, libro);
        grupo->pilas = p;
    }
    else
    {
        // Buscar la pila adecuada basándose en la fecha de publicación del libro.
        for (i = 0; i < grupo->num_pilas; i++)
        {
            // Comparar la fecha de publicación del libro con la fecha de la pila actual.
            // Si el libro es más reciente o tiene la misma fecha, apílalo en esa pila.
            if (libro->release_date >= grupo->pilas[i].cima->libro->release_date)
            {
                insertar(&grupo->pilas[i], libro);
                return;
            }
        }

        // Si el libro es más antiguo que todas las pilas existentes, crear una nueva pila.
        grupo->num_pilas++;
        Pila_LE *p = (Pila_LE *)realloc(grupo->pilas, sizeof(Pila_LE) * grupo->num_pilas);
        if (p == NULL)
        {
            fprintf(stderr, "Error al asignar memoria para la nueva pila.\n");
            exit(EXIT_FAILURE);
        }
        grupo->pilas = p;
        iniciarlizar_pila(&grupo->pilas[(grupo->num_pilas) - 1], SIN_LIMITE);
        insertar(&grupo->pilas[(grupo->num_pilas) - 1], libro);
    }
}

void mostrar_menu(void)
{
    printf("\n\r [1] APILAR TODO");
    printf("\n\r [2] APILAR POR GENERO");
    printf("\n\r [3] APILAR POR FECHA");
    printf("\n\r [4] SALIR");
}

void imprimir_pila(Pila_LE p)
{
    printf("\n\r Lista:");
    if(!vacia(p))
    {
        Elemento *i;
        i=p.cima;
        while(i!=NULL)
        {
            printf("\n\r %d | %s ,%s",i->libro->release_date,i->libro->nombre,i->libro->genero);
            i=i->siguiente;
        }
        return;
    }
    printf(" Vacia");
}