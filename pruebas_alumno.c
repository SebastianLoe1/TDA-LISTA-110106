#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void CrearLista()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Puedo crear una lista");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La lista se creó con tamaño 0");

	pa2m_afirmar(lista_vacia(lista), "La lista está vacía");

	lista_destruir(lista);
}

void InsertarEnLista()
{
	lista_t *lista = lista_crear();

	void *e1 = (void *)0x123;
	void *e2 = (void *)0xbebecafe;
	void *e3 = (void *)0x456;
	void *e4 = (void *)0xbaba;
	void *e5 = (void *)0xBaC7ec;

	lista_insertar(lista, e1);
	pa2m_afirmar(
		lista_tamanio(lista) == 1,
		"Al insertar un elemento en la lista, el tamaño se incrementa en uno");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e1,
		     "El elemento insertado está en posición 0");

	lista_insertar(lista, e2);

	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"Al insertar un segundo elemento en la lista, el tamaño es dos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e2,
		     "El elemento insertado está en posición 1");

	lista_insertar_en_posicion(lista, e3, 1);

	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"Al insertar arbitrariamente un tercer elemento, el tamaño es 3");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == e3,
		"El elemento insertado en la posición arbitraria fue insertado correctamente");

	lista_insertar_en_posicion(lista, e4, 0);

	pa2m_afirmar(
		lista_tamanio(lista) == 4,
		"Al insertar arbitrariamente un cuarto elemento, el tamaño es 4");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == e4,
		"El elemento insertado en la posición 0 fue insertado correctamente");

	lista_insertar_en_posicion(lista, e5, 100);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 4) == e5,
		"El quinto elemento insertado en una posición mayor a la de la cantidad de elementos fue insertado en la última posición");

	pa2m_afirmar(lista_primero(lista) == e4,
		     "El primer elemento de la lista es correcto");
	pa2m_afirmar(
		lista_ultimo(lista) == e5,
		"El último elemento de la lista estáen posición 4 y es el correcto");

	lista_destruir(lista);
}

void QuitarDeLista()
{
	lista_t *lista = lista_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	lista_insertar(lista, e1);
	lista_insertar(lista, e2);
	lista_insertar(lista, e3);
	lista_insertar(lista, e4);
	lista_insertar(lista, e5);

	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se insertan 5 elementos en la lista");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == e4,
		     "El elemento de la cuarta posición es el correcto");

	lista_quitar(lista);

	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "Quitado un elemento, ahora hay 4 elementos");

	lista_quitar_de_posicion(lista, 1);

	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"Quitado un segundo elemento arbitrariamente, ahora hay 3 elementos");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == e3,
		"El elemento en la posición en la que estaba el elemento quitado es el elemento correcto");

	lista_quitar_de_posicion(lista, 0);

	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"Quitado un tercer elemento arbitrariamente en la posición 0, ahora hay 2 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e3,
		     "El elemento en la posición quitada es el correcto");

	lista_quitar_de_posicion(lista, 100);

	pa2m_afirmar(
		lista_tamanio(lista) == 1,
		"Quitado un cuarto elemento arbitrariamente en una posición mayor a la cantidad de elementos quita el último de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e3,
		     "El elemento en la posición 0 es el correcto");
	pa2m_afirmar(
		lista_primero(lista) == e3,
		"El primer elemento de la lista está en la posición 0 y es correcto");
	pa2m_afirmar(
		lista_ultimo(lista) == e3,
		"El último elemento de la lista está en la posición 0 y es correcto");

	lista_quitar(lista);

	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "Se quita el elemento restante y ahora hay 0 elementos");
	pa2m_afirmar(lista_vacia(lista), "La lista vuelve a estar vacía");

	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "No se puede quitar un elemento de una lista vacía");

	lista_destruir(lista);
}

void ProbarIteradorExterno()
{
	lista_t *lista = lista_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	lista_insertar(lista, e1);
	lista_insertar(lista, e2);
	lista_insertar(lista, e3);
	lista_insertar(lista, e4);
	lista_insertar(lista, e5);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL, "Se crea un iterador correctamente");

	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == e1,
		     "El elemento en la posición 0 es correcto");

	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"En la posición 0 de 4, se afirma que el iterador tiene siguiente");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == e2,
		"El iterador avanza correctamente a la siguiente posición");

	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"En la posición 1 de 4, se afirma que el iterador tiene siguiente");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == e3,
		"El iterador avanza correctamente a la siguiente posición");

	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"En la posición 2 de 4, se afirma que el iterador tiene siguiente");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == e4,
		"El iterador avanza correctamente a la siguiente posición");

	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"En la posición 3 de 4, se afirma que el iterador tiene siguiente");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == e5,
		"El iterador avanza correctamente a la siguiente posición");

	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"En la posición 4 de 4, se afirma que el elemento siguiente es NULL");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == NULL,
		"El iterador avanza correctamente a la siguiente posición");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
		     "El iterador no tiene siguiente de una última posición");
	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "El iterador no puede avanzar a una posición inexistente");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void CrearPila()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "Se crea correctamente una pila");
	pa2m_afirmar(pila_tamanio(pila) == 0,
		     "La pila recién creada tiene tamaño 0");
	pa2m_afirmar(pila_vacia(pila), "La pila recién creada está vacía");

	pila_destruir(pila);
}

void PilaApilar()
{
	pila_t *pila = pila_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	pila_apilar(pila, e1);

	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "Se inserta correctamente un elemento en la pila");
	pa2m_afirmar(pila_tope(pila) == e1,
		     "El elemento insertado es el correcto");

	pila_apilar(pila, e2);

	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "Se inserta correctamente un elemento en la pila");
	pa2m_afirmar(pila_tope(pila) == e2,
		     "El elemento insertado es el correcto");

	pila_apilar(pila, e3);

	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "Se inserta correctamente un elemento en la pila");
	pa2m_afirmar(pila_tope(pila) == e3,
		     "El elemento insertado es el correcto");

	pila_apilar(pila, e4);

	pa2m_afirmar(pila_tamanio(pila) == 4,
		     "Se inserta correctamente un elemento en la pila");
	pa2m_afirmar(pila_tope(pila) == e4,
		     "El elemento insertado es el correcto");

	pila_apilar(pila, e5);

	pa2m_afirmar(pila_tamanio(pila) == 5,
		     "Se inserta correctamente un elemento en la pila");
	pa2m_afirmar(pila_tope(pila) == e5,
		     "El elemento insertado es el correcto");

	pila_destruir(pila);
}

void PilaDesapilar()
{
	pila_t *pila = pila_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	pila_apilar(pila, e1);
	pila_apilar(pila, e2);
	pila_apilar(pila, e3);
	pila_apilar(pila, e4);
	pila_apilar(pila, e5);

	pila_desapilar(pila);

	pa2m_afirmar(pila_tamanio(pila) == 4,
		     "De una pila de 5 elementos se quita uno y quedan 4");
	pa2m_afirmar(pila_tope(pila) == e4, "El elemento tope es el correcto");

	pila_desapilar(pila);

	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "De una pila de 5 elementos se quita uno y quedan 3");
	pa2m_afirmar(pila_tope(pila) == e3, "El elemento tope es el correcto");

	pila_desapilar(pila);

	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "De una pila de 5 elementos se quita uno y quedan 2");
	pa2m_afirmar(pila_tope(pila) == e2, "El elemento tope es el correcto");

	pila_desapilar(pila);

	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "De una pila de 5 elementos se quita uno y queda 1");
	pa2m_afirmar(pila_tope(pila) == e1, "El elemento tope es el correcto");

	pila_desapilar(pila);

	pa2m_afirmar(
		pila_tamanio(pila) == 0,
		"De una pila de 5 elementos se quita el último elemento y la pila queda vacía");
	pa2m_afirmar(pila_tope(pila) == NULL, "El elemento tope es null");

	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "No se puede quitar más elementos de una pila vacía");
	pila_destruir(pila);
}

void CrearCola()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "Se crea correctamente una cola");
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "La cola recién creada tiene tamaño 0");
	pa2m_afirmar(cola_vacia(cola), "La cola recién creada está vacía");

	cola_destruir(cola);
}

void ColaEncolar()
{
	cola_t *cola = cola_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	cola_encolar(cola, e1);

	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "Se inserta correctamente un elemento en la cola");
	pa2m_afirmar(cola_frente(cola) == e1,
		     "El elemento insertado está en el frente");

	cola_encolar(cola, e2);

	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "Se inserta correctamente un elemento en la cola");
	pa2m_afirmar(
		cola_frente(cola) != e2,
		"El elemento en el frente no es el recientemente encolado");

	cola_encolar(cola, e3);

	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "Se inserta correctamente un elemento en la cola");
	pa2m_afirmar(
		cola_frente(cola) != e3,
		"El elemento en el frente no es el recientemente encolado");

	cola_encolar(cola, e4);

	pa2m_afirmar(cola_tamanio(cola) == 4,
		     "Se inserta correctamente un elemento en la cola");
	pa2m_afirmar(
		cola_frente(cola) != e4,
		"El elemento en el frente no es el recientemente encolado");

	cola_encolar(cola, e5);

	pa2m_afirmar(cola_tamanio(cola) == 5,
		     "Se inserta correctamente un elemento en la cola");
	pa2m_afirmar(
		cola_frente(cola) != e5,
		"El elemento en el frente no es el recientemente encolado");

	cola_destruir(cola);
}

void ColaDesencolar()
{
	cola_t *cola = cola_crear();

	void *e1 = (void *)0xaaa;
	void *e2 = (void *)0xbbb;
	void *e3 = (void *)0xccc;
	void *e4 = (void *)0x789;
	void *e5 = (void *)0xcafef00d;

	cola_encolar(cola, e1);
	cola_encolar(cola, e2);
	cola_encolar(cola, e3);
	cola_encolar(cola, e4);
	cola_encolar(cola, e5);

	cola_desencolar(cola);

	pa2m_afirmar(cola_tamanio(cola) == 4,
		     "De una cola de 5 elementos se quita uno y quedan 4");
	pa2m_afirmar(cola_frente(cola) == e2,
		     "El elemento tope es el correcto");

	cola_desencolar(cola);

	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "De una cola de 5 elementos se quita uno y quedan 3");
	pa2m_afirmar(cola_frente(cola) == e3,
		     "El elemento tope es el correcto");

	cola_desencolar(cola);

	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "De una cola de 5 elementos se quita uno y quedan 2");
	pa2m_afirmar(cola_frente(cola) == e4,
		     "El elemento tope es el correcto");

	cola_desencolar(cola);

	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "De una cola de 5 elementos se quita uno y queda 1");
	pa2m_afirmar(cola_frente(cola) == e5,
		     "El elemento tope es el correcto");

	cola_desencolar(cola);

	pa2m_afirmar(
		cola_tamanio(cola) == 0,
		"De una cola de 5 elementos se quita el último elemento y la cola queda vacía");
	pa2m_afirmar(cola_frente(cola) == NULL, "El elemento tope es null");

	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "No se puede quitar más elementos de una cola vacía");

	cola_destruir(cola);
}

int main()
{
	lista_t *lista = NULL;

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Creación de Lista ========================");
	CrearLista(lista);

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Inserción y Buscado (simple y arbitraria) ========================");
	InsertarEnLista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Quitado y Buscado (simple y arbitraria) ========================");
	QuitarDeLista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas del Iterador Externo ========================");
	ProbarIteradorExterno();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Pila ========================");
	CrearPila();
	PilaApilar();
	PilaDesapilar();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Cola ========================");
	CrearCola();
	ColaEncolar();
	ColaDesencolar();

	return pa2m_mostrar_reporte();
}
