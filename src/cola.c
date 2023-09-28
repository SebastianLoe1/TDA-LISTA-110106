#include "cola.h"

typedef struct nodo {
    void *elemento;
    struct nodo *siguiente;
} nodo_t;

struct _cola_t {
    nodo_t *inicio;
    nodo_t *fin;
    size_t cantidad;
};

cola_t *cola_crear()
{
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola) {
        return NULL;
    }
    cola->inicio = NULL;
    cola->fin = NULL;
    cola->cantidad = 0;
    return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
    if (!cola) {
        return NULL;
    }

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo) {
        return NULL;
    }
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;

    if (!cola->inicio) {
        cola->inicio = nuevo_nodo;
    } else {
        cola->fin->siguiente = nuevo_nodo;
    }

    cola->fin = nuevo_nodo;
    cola->cantidad++;
    return cola;
}

void *cola_desencolar(cola_t *cola)
{
    if (!cola || cola->cantidad == 0) {
        return NULL;
    }

    nodo_t *nodo_a_eliminar = cola->inicio;
    void *elemento = nodo_a_eliminar->elemento;
    cola->inicio = nodo_a_eliminar->siguiente;

    if (!cola->inicio) {
        cola->fin = NULL;
    }

    free(nodo_a_eliminar);
    cola->cantidad--;
    return elemento;
}

void *cola_frente(cola_t *cola)
{
    if (!cola || cola->cantidad == 0) {
        return NULL;
    }
    return cola->inicio->elemento;
}

size_t cola_tamanio(cola_t *cola)
{
    if (!cola) {
        return 0;
    }
    return cola->cantidad;
}

bool cola_vacia(cola_t *cola)
{
    if (!cola || cola->cantidad == 0) {
        return true;
    }
    return false;
}

void cola_destruir(cola_t *cola)
{
    if (!cola) {
        return;
    }

    nodo_t *nodo_actual = cola->inicio;
    while (nodo_actual) {
        nodo_t *nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }

    free(cola);
}


/*
struct _cola_t {
    lista_t *lista;
};

cola_t *cola_crear()
{
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola) {
        return NULL;
    }
    cola->lista = lista_crear();
    if (!cola->lista) {
        free(cola);
        return NULL;
    }
    return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
    if (!cola) {
        return NULL;
    }
    lista_insertar(cola->lista, elemento);
    return cola;
}

void *cola_desencolar(cola_t *cola)
{
    if (!cola || lista_vacia(cola->lista)) {
        return NULL;
    }
    return lista_quitar(cola->lista);
}

void *cola_frente(cola_t *cola)
{
    if (!cola || lista_vacia(cola->lista)) {
        return NULL;
    }
    return lista_primero(cola->lista);
}

size_t cola_tamanio(cola_t *cola)
{
    if (!cola) {
        return 0;
    }
    return lista_tamanio(cola->lista);
}

bool cola_vacia(cola_t *cola)
{
    if (!cola) {
        return true;
    }
    return lista_vacia(cola->lista);
}

void cola_destruir(cola_t *cola)
{
    if (!cola) {
        return;
    }
    lista_destruir(cola->lista);
    free(cola);
}*/