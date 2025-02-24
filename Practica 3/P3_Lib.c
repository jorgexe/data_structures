#include "P3_Lib.h"

void get_pila_of_books(Pila_LE *p_books)
{
    int i;
    iniciarlizar_pila(p_books,44);
    Book books[44] = {
    {"Cell","Horror",2006},
    {"The Street Lawyer","Thriller",1998},
    {"Nineteen Minutes","Thriller",2007},
    {"Harry Potter y la piedra filosofal","Fantasy",1997},
    {"Armageddon","Post-apocalyptic fiction",2003},
    {"The Jester","Historical fiction",2003},
    {"Harry Potter y el prisionero de Azkaban","Fantasy",1999},
    {"Star Wars: Episode I The Phantom Menace","Science fiction",1999},
    {"Dreamcatcher","Fantasy",2001},
    {"Rainbow Six","Thriller",1998},
    {"Hannibal","Horror",1999},
    {"Twelve Sharp","Crime",2006},
    {"The Bear and the Dragon","Thriller",2000},
    {"The Testament","Adventure Story",1999},
    {"Red Rabbit","Historical fiction",2002},
    {"Anansi Boys","Fantasy",2005},
    {"Airframe","Thriller",1997},
    {"Harry Potter y la camara secreta","Fantasy",1998},
    {"The King of Torts","Thriller",2003},
    {"The Da Vinci Code","Mystery",2003},
    {"Harry Potter y la Orden del Fenix","Fantasy",2003},
    {"Mary, Mary","Crime",2005},
    {"The Summons","Thriller",2002},
    {"Bag of Bones","Horror",1998},
    {"The 5th Horseman","Thriller",2006},
    {"Step on a Crack","Thriller",2007},
    {"Winter's Heart","Fantasy",2000},
    {"Plum Island","Fiction",1997},
    {"Eleven on Top","Crime",2005},
    {"Harry Potter y el misterio del principe","Fantasy",2005},
    {"The Closers","Crime",2005},
    {"Glorious Appearing","Post-apocalyptic fiction",2004},
    {"Prey ","Science fiction",2002},
    {"The Last Juror","Thriller",2004},
    {"'S' Is for Silence","Mystery",2005},
    {"4th of July","Mystery",2005},
    {"Harry Potter y las reliquias de la Muerte","Fantasy",2007},
    {"The Shelters of Stone","Historical fiction",2002},
    {"Harry Potter y el caliz de fuego","Fantasy",2000},
    {"The Dark Tower VII: The Dark Tower","Fantasy",2004},
    {"Book of the Dead ","Crime",2007},
    {"The Dark Tower VI: Song of Susannah","Fantasy",2004},
    {"Cold Mountain","Historical novel",1997},
    {"A Feast for Crows","Fantasy",2005},
    };

    for(i=0;i<(p_books->longitud);i++)
    {
        insertar(p_books,&books[i]);
    }
}

void iniciarlizar_pila(Pila_LE *pila,int longitud)
{
    pila->cima=NULL;
    pila->num_elementos=0;
    pila->longitud=longitud;
}


int llena(Pila_LE p)
{
    // 1 : Pila llena
    // 0 : Hay espacio todavia
    return (p.longitud!=SIN_LIMITE && p.num_elementos==p.longitud);
}

int vacia(Pila_LE p)
{
    // 1 : Pila vacia
    // 0 : Pila contiene datos
    return ( p.cima==NULL && p.num_elementos==0);
}

void insertar(Pila_LE *p,Book *libro)
{
    if(!llena(*p))
    {
        Elemento *e= (Elemento *) malloc(sizeof(Elemento));
        e->libro   = (Book *) malloc(sizeof(Book));
        e->libro->nombre= libro->nombre;
        e->libro->genero= libro->genero;
        e->libro->release_date= libro->release_date;
        e->siguiente= p->cima;
        p->cima=e;
        p->num_elementos++;
        return;
    }
    printf("\n\r Overflow");
    return;
}

Book *mover(Pila_LE *p)
{
    if(!vacia(*p))
    {
        Book *libro;
        Elemento *e=p->cima;
        p->cima=p->cima->siguiente;
        p->num_elementos--;
        libro= e->libro;
        free(e);
        return libro;
    }
    printf("\n\r Underflow");
    return NULL;
}

void quitar(Pila_LE *p)
{
    if(!vacia(*p))
    {
        Elemento *e=p->cima;
        p->cima=p->cima->siguiente;
        p->num_elementos--;
        free(e);
        return;
    }
    printf("\n\r Underflow");
    return;
}