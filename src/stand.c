#include <stdio.h>
#include <stdlib.h>

#include "stand.h"

float calcularArea(const Stand *stand) {
    if (stand == NULL) {
    return 0;
}
    return stand->ancho * stand->largo;
}

const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: 
           return "Disponible";
        case RESERVADO: 
           return "Reservado";
        case VENDIDO:    
           return "Vendido";
        default:         
           return "Desconocido";
    }
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *)malloc(sizeof(Stand));

    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;

    nuevo->siguiente = NULL;
    return nuevo;
}

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    Stand*actual;
    if (*cabeza == NULL) {
        *cabeza=nuevo;
        return;
    }
    if (calcularArea(nuevo) < calcularArea(*cabeza)) { 
        nuevo->siguiente= *cabeza; 
        *cabeza = nuevo; 
        return; } 
        actual=*cabeza; 
    /*Encuentra la posicion dende debe estar el nuevo stand anexado */
     while (actual->siguiente!=NULL && calcularArea(actual->siguiente)<=calcularArea(nuevo)){ 
        actual= actual-> siguiente;
     }
      /*Inserta el nuevo nodo*/ 
       nuevo->siguiente= actual->siguiente;
       actual->siguiente= nuevo;

}

Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *actual; 
    Stand *anterior;
    actual = buscarStand(*cabeza, numero);
    if (actual == NULL) {
        return 0;
    }
    if (actual== NULL) {
        return 0;
    }
    if (actual == *cabeza){
         *cabeza = actual-> siguiente; 
        }
         else{ 
            anterior= *cabeza; 
            while (anterior->siguiente!=actual){
                anterior = anterior->siguiente; 
            } 
             anterior->siguiente = actual->siguiente;
             }
             actual->ancho= ancho; 
             actual->largo= largo;
             actual->estado= estado;
              
            actual->siguiente= NULL; 
             insertarOrdenadoPorArea(cabeza, actual);
              return 1;
}

int borrarStand(Stand **cabeza, int numero) {
    Stand *actual; 
    Stand *anterior = NULL;
    actual= *cabeza;
    while (actual!= NULL){ 
        if(actual-> numero == numero){
             if (anterior==NULL){ 
                *cabeza = actual->siguiente; 
            }
            else{ 
                anterior-> siguiente = actual ->siguiente; 
            }
             free(actual);/*liberamos memoria */ 
             return 1; 
            } 
            anterior = actual; actual = actual-> siguiente; 
        } 
        return 0;
     }

void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza; 
    if(actual == NULL)
    {
         printf("\nLa lista esta vacia.\n"); 
         return; 
    } 
    printf(" Lista de Stands. \n");
     while (actual != NULL){
        printf("Stand %d\n", actual->numero); 
        printf("Ancho: %.2f\n",actual->ancho ); 
        printf("Largo: %.2f\n", actual->largo);
        printf("Área: %.2f\n", calcularArea(actual)); 
        printf("Precio: %.2f\n", calcularArea(actual)*1000);
        printf("Estado: %s\n", estadoAString(actual->estado));
        actual=actual->siguiente;
     }
     printf("\n");
    
}

void liberarLista(Stand **cabeza) {
    Stand *actual; 
    Stand *siguiente; 
    actual = *cabeza;
    while (actual != NULL) { 
        siguiente = actual->siguiente;
        free(actual); 
        actual = siguiente; 
        
    } *cabeza=NULL;
}
