//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 1
//TEMA: LISTAS ENLAZADAS SIMPLES
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 64
#define CANTIDAD_ARTICULOS 15
#define VERDADERO 1
#define FALSO 0

typedef struct item
{
    char nombre[ARRAY_SIZE];
    double precio;
}Item;

Item articulos[CANTIDAD_ARTICULOS] = {
    {"Papas Fritas 105gr",15.50},
    {"Refresco 1Lt",20},
    {"Manzana  1Kg",56.40},
    {"Naranja  1Kg",46.50},
    {"Leche 30 pzas",76.00},
    {"Tomate 1Kg",24.95},
    {"Lechuga 1pza",19.20},
    {"Barra de Pan",40},
    {"Galletas ",36.60},
    {"Aguacate 1pza",9.50},
    {"Mayonesa ",32.70},
    {"Papas 1Kg",51.30},
    {"Frijo 1Kg",36.0},
    {"Arroz 1Kg",29.0},
    {"Agua Garrafon",59.00}
};

typedef struct list
{
    Item articulo;
    struct list *siguiente;
}List;

//PROTOTIPOS DE FUNCION PARA CREAR NODOS
void crear_articulo(List **art_list,Item articulo);
void insertar_articulo(List **inicio_lista,Item articulo);
void recorrer_lista(List *inicio_lista);
int lista_vacia(List *inicio_lista);
double calcular_total(List *inicio_lista);
void eliminar_ultimo(List **inicio_lista);
void eliminar_articulo(List **inicio_lista,Item articulo);

int main(void)
{
    char option;
    int num_articulo;
    int corre_programa=VERDADERO;

    List *inicio_lista;
    inicio_lista = NULL;

    while(corre_programa)
    {
        fflush(stdin);
        printf("\n OPCIONES: \n");
        printf("1) Insertar articulo \n");
        printf("2) Mostrar lista \n");
        printf("3) Mostrar total \n");
        printf("4) Eliminar ultimo \n");
        printf("5) Eliminar articulo \n");
        printf("6) Salir \n");
        printf("Escoge opcion: ");
        scanf("%c",&option);

        switch(option)
        {
            case '1':
                //menu de articulos
                printf("\n\n --- Articulos --- \n\n");
                int contador = 0;
                for(int i=0;i<CANTIDAD_ARTICULOS;i++){
                    printf("[%d] %s: $%.2lf \n",contador,articulos[i].nombre,articulos[i].precio);
                    contador++;
                }
                printf("\n Insertar articulo: ");
                scanf("%d",&num_articulo);
                insertar_articulo(&inicio_lista,articulos[num_articulo]);
                break;
            case '2':
                recorrer_lista(inicio_lista);
                printf("\n");
                //system("pause");
                break;
            case '3':
                printf("\n Total: $%.2lf \n",calcular_total(inicio_lista));
                //system("pause");
                break;
            case '4':
                eliminar_ultimo(&inicio_lista);
                break;
            case '5':
                //menu de articulos
                printf("\n\n --- Articulos --- \n\n");
                int contador1 = 0;
                for(int i=0;i<CANTIDAD_ARTICULOS;i++){
                    printf("[%d] %s: $%.2lf \n",contador1,articulos[i].nombre,articulos[i].precio);
                    contador1++;
                }
                printf("\n Eliminar articulo: ");
                scanf("%d",&num_articulo);
                eliminar_articulo(&inicio_lista,articulos[num_articulo]);
                break;
            case '6':
                corre_programa=FALSO;
                break;
            default:
                break;

        }
        //system("clear");
    }

    printf("\n\n\n\n\n------------------------------------------");
    return 0;
}

void crear_articulo(List **art_list,Item articulo)
{
    //ASIGNAR MEMORIA Y GUARDAR LA DIRECCION EN (*art_list)
    (*art_list)= malloc(sizeof(List));
    strncpy((*art_list)->articulo.nombre,articulo.nombre,ARRAY_SIZE);
    (*art_list)->articulo.precio = articulo.precio;
    (*art_list)->siguiente = NULL;
}

void insertar_articulo(List **inicio_lista,Item articulo)
{
    //SI LA LISTA ESTA VACIA,CREAR EL PRIMER NODO
    if(*inicio_lista==NULL)
    {
        crear_articulo(inicio_lista,articulo);
    }
    //SI LA LISTA NO ESTA VACIA,CREAR UN NODO E INSERTARLO AL FINAL DE LA LISTA
    else
    {
        //CREAR NODO
        List *nuevo_nodo;
        crear_articulo(&nuevo_nodo,articulo);
        //APOYARNOS DE UN APUNTARDO "p", PARA RECORRER LA LISTA HASTA ULTIMO NODO
        //SIN PERDER LA REFERENCIA DEL NODO INICIAL
        List *p=*inicio_lista;
        while(p->siguiente!=NULL)
        {
            p=p->siguiente;
        }
        //INSERCION: HACER EL ENLACE DEL ULTIMO NODO ACTUAL CON EL NUEVO NODO CREADO
        //AHORA EL NUEVO NODO SERA EL ULTIMO NODO DE LA LISTA
        p->siguiente=nuevo_nodo;
    }
}

void recorrer_lista(List *inicio_lista)
{
    List *p=inicio_lista;
    //VERIFICAR QUE LA LISTA NO ESTE VACIA
    if(p!=NULL)
    {
        //INTERAR LA LISTA HASTA LLEGAR AL ULTIMO NODO
        printf("\n --- Lista de articulos agregados --- \n\n");
        int contador = 0;
        while(p!=NULL)
        {
            printf("[%d] %s: $%.2lf \n",contador,p->articulo.nombre,p->articulo.precio);
            p = p->siguiente;
            contador++;
            //if(p!=NULL)
                //printf("-> ");
        }
        printf("\n ------------------------ \n");
    }
    //DESPLEGAR "Vacio" SI LA LISTA NO TIENE NODOS
    else
    {
        printf("Vacio");
    }
}

int lista_vacia(List *inicio_lista){
    if(inicio_lista==NULL)
        return VERDADERO;
    else
        return FALSO;
}

double calcular_total(List *inicio_lista){
    double total=0;
    List *p=inicio_lista;
    while(p!=NULL){
        total+=p->articulo.precio;
        p=p->siguiente;
    }
    return total;
}

void eliminar_ultimo(List **inicio_lista){
    List *p=*inicio_lista;
    List *q=*inicio_lista;
    if(p!=NULL){
        if(p->siguiente==NULL){
            free(p);
            *inicio_lista=NULL;
        }
        else{
            while(p->siguiente!=NULL){
                q=p;
                p=p->siguiente;
            }
            q->siguiente=NULL;
            free(p);
        }
    }
}

void eliminar_articulo(List **inicio_lista,Item articulo){
    List *p=*inicio_lista;
    List *q=*inicio_lista;
    if(p!=NULL){
        if(strcmp(p->articulo.nombre,articulo.nombre)==0){
            *inicio_lista=p->siguiente;
            free(p);
        }
        else{
            while(p!=NULL && strcmp(p->articulo.nombre,articulo.nombre)!=0){
                q=p;
                p=p->siguiente;
            }
            if(p!=NULL){
                q->siguiente=p->siguiente;
                free(p);
            }
        }
    }
}