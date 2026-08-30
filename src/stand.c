#include <stdio.h>
#include <stdlib.h>

#include "stand.h"

float calcularArea(const Stand *stand) {
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
    Stand *actual;

    if (cabeza == NULL || nuevo == NULL) {
        return;
    }

    if (*cabeza == NULL || calcularArea(nuevo) <= calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    actual = *cabeza;

    while (actual->siguiente != NULL &&
           calcularArea(actual->siguiente) < calcularArea(nuevo)) {
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
    Stand *actual;
    Stand *anterior = NULL;
    int cambioDimensiones;

    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    actual = *cabeza;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    cambioDimensiones = (actual->ancho != ancho) || (actual->largo != largo);

    actual->ancho = ancho;
    actual->largo = largo;
    actual->estado = estado;

    if (cambioDimensiones) {
        if (anterior == NULL) {
            *cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        actual->siguiente = NULL;
        insertarOrdenadoPorArea(cabeza, actual);
    }

    return 1;
}

int borrarStand(Stand **cabeza, int numero) {
    Stand *actual;
    Stand *anterior = NULL;

    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    actual = *cabeza;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    return 1;
}

void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;

    if (actual == NULL) {
        printf("[Lista vacía]\n");
        return;
    }

    while (actual != NULL) {
        printf("Stand #%d | %.2fm x %.2fm | Área: %.2fm2 | Estado: %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual),
               estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    Stand *actual;
    Stand *siguiente;

    if (cabeza == NULL) {
        return;
    }

    actual = *cabeza;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *cabeza = NULL;
}
