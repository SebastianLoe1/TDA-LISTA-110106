#include "pila.h"
#include "lista.h"

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


/*struct _pila_t {
    lista_t *lista;
};

pila_t *pila_crear()
{
    pila_t *pila = malloc(sizeof(pila_t));
    if (!pila) {
        return NULL;
    }
    pila->lista = lista_crear();
    if (!pila->lista) {
        free(pila);
        return NULL;
    }
    return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
    if (!pila) {
        return NULL;
    }
    lista_insertar(pila->lista, elemento);
    return pila;
}

void *pila_desapilar(pila_t *pila)
{
    if (!pila || lista_vacia(pila->lista)) {
        return NULL;
    }
    return lista_quitar_de_posicion(pila->lista, 0);
}

void *pila_tope(pila_t *pila)
{
    if (!pila || lista_vacia(pila->lista)) {
        return NULL;
    }
    size_t tamanio = lista_tamanio(pila->lista);
    return lista_elemento_en_posicion(pila->lista, tamanio - 1);
}

size_t pila_tamanio(pila_t *pila)
{
    if (!pila) {
        return 0;
    }
    return lista_tamanio(pila->lista);
}

bool pila_vacia(pila_t *pila)
{
    if (!pila) {
        return true;
    }
    return lista_vacia(pila->lista);
}

void pila_destruir(pila_t *pila)
{
    if (!pila) {
        return;
    }
    lista_destruir(pila->lista);
    free(pila);
}*/