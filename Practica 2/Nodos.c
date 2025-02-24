#include "Nodos.h"
#include "Customlib.h"

int agregar_nodo(LISTA_2E *lista,Cancion song,int posicion)
{
    //INSERTAR PRIMER NODO
    if(lista->inicio==NULL && lista->inicio==NULL && lista->num_nodos==0)
    {
        crear_Nodo(&(lista->inicio),song);
        lista->fin=lista->inicio;
        lista->num_nodos++;
        return 1;
    }
    //INSERTAR AL FINAL
    else if(posicion==FINAL)
    {
        // Crear nodo
        Nodo *nuevo_nodo;
        crear_Nodo(&nuevo_nodo, song);
        
        // Hacer enlaces
        nuevo_nodo->anterior = lista->fin;
        lista->fin->siguiente = nuevo_nodo;
        lista->fin = nuevo_nodo;
        
        // Incrementar numero de nodos
        lista->num_nodos++;
        return 1;
    }
    //INSERTAR AL INICIO
    else if(posicion==INICIO)
    {
        //IMPLEMENTAR INSERTAR AL INICIO
        // Crear nodo
        Nodo *nuevo_nodo;
        crear_Nodo(&nuevo_nodo, song);

        // Hacer enlaces
        nuevo_nodo->siguiente = lista->inicio;
        lista->inicio->anterior = nuevo_nodo;
        lista->inicio = nuevo_nodo;

        // Incrementar numero de nodos
        lista->num_nodos++;
        return 1;
    }
    //INSERTAR EN POSICION
    else if(posicion>INICIO && posicion<=(lista->num_nodos - 1))
    {
        //IMPLEMENTAR INSERTAR EN POSICION
        int i,j;
        i=0;
        j=(lista->num_nodos - 1);
        Nodo *p=lista->inicio;
        Nodo *q=lista->fin;
        Nodo *nuevo_nodo;
        //CREAR NODO 
        crear_Nodo(&nuevo_nodo,song);
        while(posicion!=i && posicion!=j)
        {
            p=p->siguiente;
            i++;
            q=q->anterior;
            j--;
        }
        p = (posicion==i) ? p : q;
        nuevo_nodo->anterior = p->anterior;
        nuevo_nodo->siguiente= p;
        p->anterior->siguiente= nuevo_nodo;
        p->anterior= nuevo_nodo;
        lista->num_nodos++;
        return 1;

    }
    //POSICION NO VALIDA, NO SE REALIZA INSERCION
    else
    {
        return 0;
    }
}

int eliminar_nodo(LISTA_2E *lista,int posicion)
{
    if(lista->num_nodos==0)
    {
        return 0;
    }
    else if(lista->num_nodos==1 && (posicion==INICIO || posicion==FINAL || posicion==(lista->num_nodos-1)))
    {
        Nodo *p=lista->inicio;
        lista->inicio = NULL;
        lista->fin = NULL;
        free(p);
        lista->num_nodos--;
        return 1;
    }
    else if(posicion==INICIO)
    {
        //ELIMINAR PRIMER NODO
        // Verificar si la lista tiene solo un nodo
        if (lista->num_nodos == 1) {
            Nodo *p = lista->inicio;
            lista->inicio = NULL;
                lista->fin = NULL;
            free(p); // Liberar el nodo
            lista->num_nodos--; // Decrementar el número de nodos
            return 1; // Indicar éxito
        } else {
            Nodo *p = lista->inicio;
            lista->inicio = p->siguiente;
            lista->inicio->anterior = NULL;
            free(p); // Liberar el nodo
            lista->num_nodos--; // Decrementar el número de nodos
            return 1; // Indicar éxito
        }
    }
    else if(posicion==FINAL || posicion==(lista->num_nodos-1))
    {
        //ELIMINAR ULTIMO NODO
        // Verificar si hay un solo nodo en la lista
        if (lista->num_nodos == 1) {
            Nodo *p = lista->inicio;
            lista->inicio = NULL;
            lista->fin = NULL;
            free(p);
            lista->num_nodos--;
            return 1;
        } else {
            Nodo *p=lista->fin;
            lista->fin = p->anterior;
            lista->fin->siguiente= NULL;
            free(p);
            lista->num_nodos--;
            return 1;
        }
    }
    else if(posicion>INICIO && posicion<(lista->num_nodos - 1))
    {
        //ELIMINAR NODO EN POSICION
        int i,j;
        i=0;
        j=(lista->num_nodos - 1);
        Nodo *p=lista->inicio;
        Nodo *q=lista->fin;
        while(posicion!=i && posicion!=j)
        {
            p=p->siguiente;
            i++;
            q=q->anterior;
            j--;
        }
        p = (posicion==i) ? p : q;
        p->anterior->siguiente= p->siguiente;
        p->siguiente->anterior= p->anterior;
        free(p);
        lista->num_nodos--;
        return 1;
    }
    else
    {
        return 0;
    }
}


void crear_Nodo(Nodo **nodo,Cancion song)
{
    //ASIGNAR MEMORIA Y GUARDAR LA DIRECCION EN (*NODO)
    (*nodo)= malloc(sizeof(Nodo));
    (*nodo)->anterior = NULL;
    strncpy((*nodo)->song.nombre,song.nombre,30);
    strncpy((*nodo)->song.artista_grupo,song.artista_grupo,20);
    (*nodo)->siguiente = NULL;
}

void recorrer_nodos(LISTA_2E param_lista,int direccion)
{
    Nodo *p=param_lista.inicio;
    int i,j;
    gotoxy(55,3);
    printf("%s","LISTA:\0");
    if(p==NULL)     //VERIFICAR QUE LA LISTA NO ESTE VACIA
    {
        gotoxy(55,4);
        printf("%s","NULL    \0");
        return;
    }
    if(direccion==INICIO_FINAL)
    {
        i=0;
        j=0;
        while(p!=NULL)  //INTERAR LA LISTA HASTA LLEGAR AL ULTIMO NODO
        {
            gotoxy(55,4+j);
            print_Nodo(p,i);
            p   = p->siguiente;
            i++;
            j++;
        }
        return;
    }
    else if(direccion==FINAL_INICIO)
    {
        p=param_lista.fin;
        i=param_lista.num_nodos-1;
        j=0;
        while(p!=NULL)  //INTERAR LA LISTA HASTA LLEGAR AL ULTIMO NODO
        {
            gotoxy(55,4+j);
            print_Nodo(p,i);
            p   = p->anterior;
            i--;
            j++;
        }
        return;
    }
    else
    {
        return;
    }
}

void print_Nodo(Nodo *p_nodo,int index)
{
    printf("[%02d] %s ,%s",index,p_nodo->song.nombre,p_nodo->song.artista_grupo);
}


void display_circular(LISTA_2E param_lista)
{
    if(param_lista.inicio!=NULL && param_lista.fin!=NULL && param_lista.num_nodos!=0)
    {
        if(param_lista.inicio->anterior!=NULL && param_lista.fin->siguiente!=NULL && param_lista.inicio->anterior==param_lista.fin->siguiente)
            printf(" Circular: Habilitado");
        else
            printf(" Circular: Deshabilidado");

    }
    else
    {
        printf(" Circular: Deshabilidado");
    }
}


void display_canciones(Cancion *songs,int length,int y)
{
    int i;
    for(i=0;i<length;i++)
    {
        gotoxy(0,y+i+4);
        printf("[%d] %s , %s",i,songs[i].nombre,songs[i].artista_grupo);
    }
}