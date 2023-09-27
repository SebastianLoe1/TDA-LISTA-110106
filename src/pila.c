#include "pila.h"

typedef struct nodo {
    void *elemento;
    struct nodo *siguiente;
} nodo_t;

struct _pila_t {
    nodo_t *tope;
    size_t cantidad;
};

pila_t *pila_crear()
{
    pila_t *pila = malloc(sizeof(pila_t));
    if (!pila) {
        return NULL;
    }
    pila->tope = NULL;
    pila->cantidad = 0;
    return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
    if (!pila) {
        return NULL;
    }

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo) {
        return NULL;
    }
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = pila->tope;
    pila->tope = nuevo_nodo;
    pila->cantidad++;
    return pila;
}

void *pila_desapilar(pila_t *pila)
{
    if (!pila || pila->cantidad == 0) {
        return NULL;
    }

    nodo_t *nodo_a_eliminar = pila->tope;
    void *elemento = nodo_a_eliminar->elemento;
    pila->tope = nodo_a_eliminar->siguiente;
    free(nodo_a_eliminar);
    pila->cantidad--;
    return elemento;
}

void *pila_tope(pila_t *pila)
{
    if (!pila || pila->cantidad == 0) {
        return NULL;
    }
    return pila->tope->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
    if (!pila) {
        return 0;
    }
    return pila->cantidad;
}

bool pila_vacia(pila_t *pila)
{
    if (!pila || pila->cantidad == 0) {
        return true;
    }
    return false;
}

void pila_destruir(pila_t *pila)
{
    if (!pila) {
        return;
    }

    nodo_t *nodo_actual = pila->tope;
    while (nodo_actual) {
        nodo_t *nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }

    free(pila);
}