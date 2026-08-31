#include <stdio.h>
#include <stdlib.h>

#include "stand.h"

float calcularArea(const Stand *stand) {
    return stand->ancho * stand->largo;
}

const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
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
    if (cabeza == NULL || nuevo == NULL) return;
    float areaNuevo = calcularArea(nuevo);
    if (*cabeza == NULL || calcularArea(*cabeza) >= areaNuevo) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNuevo) {
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
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
    Stand *encontrado = buscarStand(*cabeza, numero);
    if (encontrado == NULL) {
        return 0;
    }
    /* Allocate new node before removing the old one to avoid data loss on failure */
    Stand *nuevo = crearStand(numero, ancho, largo, estado);
    if (nuevo == NULL) {
        return 0;
    }
    borrarStand(cabeza, numero);
    insertarOrdenadoPorArea(cabeza, nuevo);
    return 1;
}

int borrarStand(Stand **cabeza, int numero) {
    if (*cabeza == NULL) {
        return 0;
    }
    if ((*cabeza)->numero == numero) {
        Stand *tmp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(tmp);
        return 1;
    }
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL) {
        if (actual->siguiente->numero == numero) {
            Stand *tmp = actual->siguiente;
            actual->siguiente = tmp->siguiente;
            free(tmp);
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL) {
        printf("  (lista vacía)\n");
        return;
    }
    const Stand *actual = cabeza;
    while (actual != NULL) {
        printf("  Stand #%d | %.1fm x %.1fm | Área: %.2fm^2 | Estado: %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual),
               estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    if (cabeza == NULL) return;
    Stand *actual = *cabeza;
    while (actual != NULL) {
        Stand *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}
