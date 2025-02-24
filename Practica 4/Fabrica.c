//UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA
//PRACTICA 4
//TEMA: COLAS
//NOMBRE: JORGE ALEJANDRO SANDOVAL ROMO
//MATRICULA: 1288599

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    CARROCERIA=1,
    TANQUE,
    MOTOR,
    PUERTAS,
    LLANTAS,
}N_Parte;

typedef struct st_parte
{
    N_Parte parte;
    struct st_parte *siguiente;
}S_Parte;

typedef enum
{
    CARROCERIA_MONTADA=1,
    TANQUE_ENSAMBLADO=2,
    MOTOR_ENSAMBLADO=3,
    PUERTAS_ENSAMBLADAS=7,
    LLANTAS_ENSAMBLADAS=11,
}N_Estado;

typedef struct st_vehiculo
{
    N_Estado estado;
    struct st_vehiculo *siguiente;
}S_Vehiculo;

typedef struct s_cola
{
    S_Parte *frente;
    S_Parte *fin;
    int num_partes;
}Cola;

typedef struct s_cola_vehiculo
{
    S_Vehiculo *frente;
    S_Vehiculo *fin;
    int num_vehiculos;
}Cola_Vehiculo;

typedef struct alm
{
    Cola carroceria;
    Cola tanque;
    Cola motor;
    Cola puertas;
    Cola llantas;
}Almacenamiento;

typedef struct ens
{
    Cola_Vehiculo tanque;
    Cola_Vehiculo motor;
    Cola_Vehiculo puertas;
    Cola_Vehiculo llantas;
}Ensamblaje;

void inicializar_almacenamiento(Cola *c);
void inicializar_ensamblaje(Cola_Vehiculo *c);
//IMPLEMENTAR
//DEL ALMACENAMIENTO
int alm_vacio(Cola c);                 //VERIFICA QUE EXISTA UNA PARTE EN EL ALMACENAMIENTO
void agregar_parte(Cola *c,N_Parte id_parte);   //SE AGREGA LA PARTE AL SU ALMACENAMIENTO
void sacar_parte(Cola *c);                      //SE SACA LA PARTE DE SU ALCEMANMIENTO

//DEL ENSAMBLAJE
int cola_vacia(Cola_Vehiculo c);                                //VERIFICA SI EN LA COLA DE ENSAMBLAJE EXISTE UN VEHICULO EN ESPERA
void agregar_vehiculo(Cola_Vehiculo *c,S_Vehiculo *vehiculo);   //SE AGREGA UN VEHICULO EN LA COLA DE ESPERA DE ENSAMBLAJE
S_Vehiculo *mover_vehiculo(Cola_Vehiculo *c);                             //SE OBTIENE EL VEHICULO Y SE SACA DE LA COLA DE ESPERA DE ENSAMBLAJE


int main(void)
{
    Almacenamiento partes;
    inicializar_almacenamiento(&partes.carroceria);
    inicializar_almacenamiento(&partes.tanque);
    inicializar_almacenamiento(&partes.motor);
    inicializar_almacenamiento(&partes.puertas);
    inicializar_almacenamiento(&partes.llantas);

    Ensamblaje colas_ensamble;
    inicializar_ensamblaje(&colas_ensamble.tanque);
    inicializar_ensamblaje(&colas_ensamble.motor);
    inicializar_ensamblaje(&colas_ensamble.puertas);
    inicializar_ensamblaje(&colas_ensamble.llantas);

    //HACER UN MENU CON LAS SIGUIENTES OPCIONES
    while(1){
        printf("1.-Fabricar Carroceria\n");
        printf("2.-Fabricar Tanque\n");
        printf("3.-Fabricar Motor\n");
        printf("4.-Fabricar Puertas\n");
        printf("5.-Fabricar Llantas\n");
        printf("6.-Iniciar Ensamblaje\n");
        printf("7.-Ensamblar Tanque\n");
        printf("8.-Ensamblar Motor\n");
        printf("9.-Ensamblar Puertas\n");
        printf("10.-Ensamblar Llantas\n");
        printf("11.-Salir\n");
        printf("Opcion: ");
        int opcion;
        scanf("%d",&opcion);
        if(opcion<1 || opcion>11){
            printf("Opcion no valida\n");
            continue;
        }

        switch(opcion){
    //-FABRICAR CARROCERIA:
        //Se crea una carroceria y se agrega a su cola de almacenamiento
        case 1:
            agregar_parte(&partes.carroceria,CARROCERIA);
            break;
        
    //-FABRICAR TANQUE:
        //Se crea un tanque de combustible y se agrega a su cola de almacenamiento
        case 2:
            agregar_parte(&partes.tanque,TANQUE);
            break;
        
    //-FABRICAR MOTOR:
        //Se crea un motor y se agrega a su cola de almacenamiento
        case 3:
            agregar_parte(&partes.motor,MOTOR);
            break;
        
    //-FABRICAR PUERTAS:
        //Se crea una puerta y se agrega a su cola de almacenamiento
        case 4:
            agregar_parte(&partes.puertas,PUERTAS);
            break;
        
    //-FABRICAR LLANTAS:
        //Se crea una llanta y se agrega a su cola de almacenamiento
        case 5:
            agregar_parte(&partes.llantas,LLANTAS);
            break;

    //-INICIAR ENSAMBLAJE
        //Se comprueba si hay carroceria en existencia, si hay se monta (CAMBIA DE ESTADO EL VEHICULO, ESTADO 1) y pasa a
        //la cola de espera de tanque de combustible
        case 6:
            // Verificar si hay carrocerías disponibles
            if (alm_vacio(partes.carroceria) == 1) {
                printf("No hay carrocerías disponibles para iniciar el ensamblaje.\n");
            } else {
                // Sacar una carrocería del almacenamiento
                sacar_parte(&partes.carroceria);

                // Crear un nuevo vehículo y configurar su estado
                S_Vehiculo *nuevo_vehiculo = (S_Vehiculo *)malloc(sizeof(S_Vehiculo));
                if (nuevo_vehiculo == NULL) {
                    printf("Error al asignar memoria para un nuevo vehículo.\n");
                    break;
                }
                nuevo_vehiculo->estado = CARROCERIA_MONTADA;
                nuevo_vehiculo->siguiente = NULL;

                // Agregar el vehículo a la cola de espera de ensamblaje para el tanque
                agregar_vehiculo(&colas_ensamble.tanque, nuevo_vehiculo);
                printf("Se ha iniciado el ensamblaje de un nuevo vehículo.\n");
            }
            break;
        
    //-ENSAMBLAR TANQUE:
        //Se comprueba si hay tanque de combustible en existencia, si hay se ensambla (CAMBIA DE ESTADO EL VEHICULO, ESTADO 2)
        //y pasa a la siguiente cola de espera, la cola de espera de motor
        case 7:
        // Verificar si hay tanques disponibles y si hay vehículos esperando ensamblaje de tanque
            if (alm_vacio(partes.tanque) == 1) {
                printf("No hay tanques de combustible disponibles para el ensamblaje.\n");
            } else if (cola_vacia(colas_ensamble.tanque) == 1) {
                printf("No hay vehículos esperando ensamblaje de tanque.\n");
            } else {
                // Sacar un tanque del almacenamiento
                sacar_parte(&partes.tanque);

                // Mover el vehículo al siguiente estado y cola
                S_Vehiculo *vehiculo = mover_vehiculo(&colas_ensamble.tanque);
                vehiculo->estado = TANQUE_ENSAMBLADO;

                // Agregar el vehículo a la cola de espera de ensamblaje para el motor
                agregar_vehiculo(&colas_ensamble.motor, vehiculo);
                printf("Se ha ensamblado el tanque de combustible en un vehículo.\n");
            }
            break;
        
    //-ENSAMBLAR MOTOR:
        //Se comprueba si hay motor en existencia, si hay se ensambla (CAMBIA DE ESTADO EL VEHICULO, ESTADO 3))
        //y pasa a la siguiente cola de espera, la cola de espera de llanta
        case 8:
            // Verificar si hay motores disponibles y si hay vehículos esperando ensamblaje de motor
            if (alm_vacio(partes.motor) == 1) {
                printf("No hay motores disponibles para el ensamblaje.\n");
            } else if (cola_vacia(colas_ensamble.motor) == 1) {
                printf("No hay vehículos esperando ensamblaje de motor.\n");
            } else {
                // Sacar un motor del almacenamiento
                sacar_parte(&partes.motor);

                // Mover el vehículo al siguiente estado y cola
                       S_Vehiculo *vehiculo = mover_vehiculo(&colas_ensamble.motor);
                vehiculo->estado = MOTOR_ENSAMBLADO;

                // Agregar el vehículo a la cola de espera de ensamblaje para las puertas
                agregar_vehiculo(&colas_ensamble.puertas, vehiculo);
                printf("Se ha ensamblado el motor en un vehículo.\n");
            }
            break;
        
    //-ENSAMBLAR PUERTA:
        //Se comprueba si hay puerta en existencia, si hay se ensambla (CAMBIA DE ESTADO EL VEHICULO, INCREMENTA)
        //y pasa a la siguiente cola de espera (SI ES QUE SE ENSAMBLARON 4 PUERTAS, ESTADO 7), la cola de espera de llanta
        case 9:
            // Verificar si hay puertas disponibles y si hay vehículos esperando ensamblaje de puertas
            if (alm_vacio(partes.puertas) == 1) {
                printf("No hay puertas disponibles para el ensamblaje.\n");
            } else if (cola_vacia(colas_ensamble.puertas) == 1) {
                printf("No hay vehículos esperando ensamblaje de puertas.\n");
            } else {
                // Sacar una puerta del almacenamiento
                sacar_parte(&partes.puertas);

                // Mover el vehículo al siguiente estado
                S_Vehiculo *vehiculo = mover_vehiculo(&colas_ensamble.puertas);
                vehiculo->estado++;

                // Verificar si todas las puertas han sido ensambladas
                if (vehiculo->estado == PUERTAS_ENSAMBLADAS) {
                    // Agregar el vehículo a la cola de espera de ensamblaje para las llantas
                    agregar_vehiculo(&colas_ensamble.llantas, vehiculo);
                    printf("Todas las puertas han sido ensambladas en un vehículo.\n");
                } else {
                    // Si aún no se han ensamblado todas las puertas, el vehículo regresa a la cola de puertas
                    agregar_vehiculo(&colas_ensamble.puertas, vehiculo);
                }
            }
            break;
        
    //-FABRICAR PUERTA:
        //Se comprueba si hay llanta en existencia, si hay se ensambla (CAMBIA DE ESTADO EL VEHICULO)
        //y pasa sacarse el vehiculo de la fabrica (SI ES QUE SE ENSAMBLARON 4 LLANTAS, ESTADO 11)
        case 10:
            // Verificar si hay llantas disponibles y si hay vehículos esperando ensamblaje de llantas
            if (alm_vacio(partes.llantas) == 1) {
                printf("No hay llantas disponibles para el ensamblaje.\n");
            } else if (cola_vacia(colas_ensamble.llantas) == 1) {
                printf("No hay vehículos esperando ensamblaje de llantas.\n");
            } else {
                // Sacar una llanta del almacenamiento
                sacar_parte(&partes.llantas);
        
                // Mover el vehículo al siguiente estado
                S_Vehiculo *vehiculo = mover_vehiculo(&colas_ensamble.llantas);
                vehiculo->estado++;
        
                // Verificar si todas las llantas han sido ensambladas
                if (vehiculo->estado == LLANTAS_ENSAMBLADAS) {
                    printf("Un vehículo ha sido completamente ensamblado.\n");
                    // Aquí se podría agregar el vehículo a una cola de vehículos terminados o similar
                } else {
                    // Si aún no se han ensamblado todas las llantas, el vehículo regresa a la cola de llantas
                    agregar_vehiculo(&colas_ensamble.llantas, vehiculo);
                }
            }
            break;
        
    //-SALIR:
        //TERMINA EL PROGRAMA
        case 11:
            return 0;
            break;
        
        break;
        }
    }

    return 0;
}

void inicializar_almacenamiento(Cola *c)
{
    c->frente=NULL;
    c->fin=NULL;
    c->num_partes=0;
}
void inicializar_ensamblaje(Cola_Vehiculo *c)
{
    c->frente=NULL;
    c->fin=NULL;
    c->num_vehiculos=0;
}

//IMPLEMENTAR
//DEL ALMACENAMIENTO
int alm_vacio(Cola c)//VERIFICA QUE EXISTA UNA PARTE EN EL ALMACENAMIENTO
{
    if(c.frente==NULL)
        return 1;

    return 0;
}

void agregar_parte(Cola *c, N_Parte id_parte) //SE AGREGA LA PARTE AL SU ALMACENAMIENTO
{
    // Crear una nueva parte
    S_Parte *nueva_parte = (S_Parte*)malloc(sizeof(S_Parte));
    if (nueva_parte == NULL) {
        printf("Error al asignar memoria para una nueva parte.\n");
        return;
    }

    // Configurar la nueva parte
    nueva_parte->parte = id_parte;
    nueva_parte->siguiente = NULL;

    // Si la cola está vacía, el frente y el fin serán la nueva parte
    if (c->frente == NULL) {
        c->frente = nueva_parte;
        c->fin = nueva_parte;
    } else {
        // Si no, se añade al final de la cola
        c->fin->siguiente = nueva_parte;
        c->fin = nueva_parte;
    }

    // Incrementar el contador de partes
    c->num_partes++;
}

//SE SACA LA PARTE DE SU ALCEMANMIENTO
void sacar_parte(Cola *c) 
{
    // Verificar si la cola está vacía
    if (c->frente == NULL) {
        printf("No hay partes en el almacenamiento para sacar.\n");
        return;
    }

    // Guardar la referencia a la parte del frente
    S_Parte *parte_a_sacar = c->frente;

    // Mover el frente al siguiente elemento
    c->frente = c->frente->siguiente;

    // Si después de mover el frente, la cola está vacía, se actualiza el fin a NULL
    if (c->frente == NULL) {
        c->fin = NULL;
    }

    // Liberar la memoria de la parte sacada
    free(parte_a_sacar);

    // Decrementar el contador de partes
    c->num_partes--;
}


//DEL ENSAMBLAJE

//VERIFICA SI EN LA COLA DE ENSAMBLAJE EXISTE UN VEHICULO EN ESPERA
int cola_vacia(Cola_Vehiculo c) {
    if (c.frente == NULL) 
        return 1; 
    return 0;
}

//SE AGREGA UN VEHICULO EN LA COLA DE ESPERA DE ENSAMBLAJE
void agregar_vehiculo(Cola_Vehiculo *c, S_Vehiculo *vehiculo) 
{
    // Verificar si el vehículo a agregar es válido
    if (vehiculo == NULL) {
        printf("El vehículo a agregar es nulo.\n");
        return;
    }

    // Configurar el siguiente vehículo del vehículo a agregar como NULL
    vehiculo->siguiente = NULL;

    // Si la cola está vacía, el vehículo a agregar es el primero
    if (c->frente == NULL) {
        c->frente = vehiculo;
        c->fin = vehiculo;
    } else {
        // Si no, añadir al final y actualizar el fin
        c->fin->siguiente = vehiculo;
        c->fin = vehiculo;
    }

    // Incrementar el contador de vehículos
    c->num_vehiculos++;
}


//SE OBTIENE EL VEHICULO Y SE SACA DE LA COLA DE ESPERA DE ENSAMBLAJE
S_Vehiculo *mover_vehiculo(Cola_Vehiculo *c) 
{
    // Verificar si la cola está vacía
    if (c->frente == NULL) {
        printf("No hay vehículos en la cola de ensamblaje para mover.\n");
        return NULL;
    }

    // Guardar la referencia al vehículo del frente
    S_Vehiculo *vehiculo_a_mover = c->frente;

    // Mover el frente al siguiente vehículo
    c->frente = c->frente->siguiente;

    // Si la cola queda vacía, actualizar el fin a NULL
    if (c->frente == NULL) {
        c->fin = NULL;
    }

    // Decrementar el contador de vehículos
    c->num_vehiculos--;

    // Devolver el vehículo retirado
    return vehiculo_a_mover;
}

