//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 2
//TEMA: LISTAS DOBLEMENTE ENLAZADAS
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include "Customlib.h"
#include "Nodos.h"
#include <windows.h>
#include <stdio.h>

#define VERDADERO 1
#define FALSO 0
#define SONGS_SIZE 12

Cadenas opt[CANTIDAD_OPCIONES] =  {
                        {"AGREGAR CANCION AL INICIO\0"},
                        {"AGREGAR CANCION AL FINAL\0"},
                        {"AGREGAR CANCION EN POSICION\0"},
                        {"ELIMINAR CANCION DEL INICIO\0"},
                        {"ELIMINAR CANCION DEL FINAL\0"},
                        {"ELIMINAR CANCION EN POSICION\0"},
                        {"RECORRER DEL INICIO AL FINAL\0"},
                        {"RECORRER DEL FINAL AL INICIO\0"},
                        {"SALIR"}
};

Cancion songs[SONGS_SIZE] = {
        {"DARE","Gorillaz"},
        {"Knights of Cydonia","Muse"},
        {"Nightcall","Kavinsky"},
        {"Personal Jesus","Depeche Mode"},
        //agregar 8 canciones
        {"Mile High","James Blake"},
        {"Heart To Heart","Mac Demarco"},
        {"my future","Billie Eilish"},
        {"LVL", "A$AP Rocky"},
        {"Need 2","Pinegrove"},
        {"It's you","Lauren Creviston"},
        {"Young","Vacations"},
        {"REBOUND!","JPEGMAFIA"}
};

void escoge_cancion(void);

int option;
int posicion;
int y;
int direccion;

int main(void)
{
        direccion=INICIO_FINAL;
        system("cls");
        //Nodo cancion;
        LISTA_2E lista;
        lista.inicio=NULL;
        lista.fin=NULL;
        lista.num_nodos=0;

        while(1){
                system("cls");
                //display_circular(lista);
                recorrer_nodos(lista,direccion);
                display_options(opt);
                y=wherey();
                captura_int(1,1,"\n\n\r ESCOGE OPCION: ",&option);
                switch(option)
                {
                case 0:
                        escoge_cancion();
                        if(option<0 || option>SONGS_SIZE-1)
                                break;
                    //GET CANCION
                        agregar_nodo(&lista,songs[option],INICIO);
                        break;
                case 1:
                        escoge_cancion();
                        if(option<0 || option>SONGS_SIZE-1)
                        break;
                        //GET CANCION
                        agregar_nodo(&lista,songs[option],FINAL);
                        //esperar_enter();
                        break;
                case 2:
                        recorrer_nodos(lista,INICIO_FINAL);
                        gotoxy(0,y+3);y++;
                        captura_int(1,3," ESCOGE POSICION: ",&posicion);
                        escoge_cancion();
                        if(option<0 || option>SONGS_SIZE-1)
                                break;
                        //GET CANCION
                        agregar_nodo(&lista,songs[option],posicion);
                        break;
                case 3:
                        eliminar_nodo(&lista,INICIO);
                        break;
                case 4:
                        eliminar_nodo(&lista,FINAL);
                        break;
                case 5:
                        recorrer_nodos(lista,INICIO_FINAL);
                        gotoxy(0,y+3);
                        captura_int(1,3," ESCOGE POSICION: ",&posicion);
                        eliminar_nodo(&lista,posicion);
                        break;
                case 6:
                        direccion=INICIO_FINAL;
                        break;
                case 7:
                        direccion=FINAL_INICIO;
                        break;
                case 8:
                        return 0;
                        break;
                default:
                        break;
        }
}

        printf("\n\n\n\n\n\r \n\r");
        return 0;
}

void escoge_cancion(void)
{
        y=wherey();
        display_canciones(songs,SONGS_SIZE,y+1);
        gotoxy(0,y+3);
        captura_int(1,2," ESCOGE CANCION: ",&option);
}