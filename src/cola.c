#include "cola.h"
#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct _cola_t {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	int cantidad;
};

cola_t *cola_crear()
{
	return (cola_t *)lista_crear();
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	lista_insertar((lista_t *)cola, elemento);
	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola || lista_vacia((lista_t *)cola)) {
		return NULL;
	}
	return lista_quitar_de_posicion((lista_t *)cola, 0);
}

void *cola_frente(cola_t *cola)
{
	if (!cola || lista_vacia((lista_t *)cola)) {
		return NULL;
	}
	return lista_primero((lista_t *)cola);
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((lista_t *)cola);
}

bool cola_vacia(cola_t *cola)
{
	return lista_vacia((lista_t *)cola);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((lista_t *)cola);
}