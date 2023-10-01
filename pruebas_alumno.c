#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void CrearLista()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Puedo crear una lista");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista se creó con tamaño 0");

	pa2m_afirmar(lista_vacia(lista), "La lista está vacía");

	lista_destruir(lista);

}

void InsertarEnLista(){
    lista_t* lista = lista_crear();


    void *e1 = (void*)0x123;
    void *e2 = (void*)0xbebecafe;
	void *e3 = (void*)0x456;
	void *e4 = (void*)0xbaba;
	void *e5 = (void*)0xBaC7ec;

    lista_insertar(lista, e1);
    pa2m_afirmar(lista_tamanio(lista) == 1, "Al insertar un elemento en la lista, el tamaño se incrementa en uno");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e1, "El elemento insertado está en posición 0");

    lista_insertar(lista, e2);

    pa2m_afirmar(lista_tamanio(lista) == 2, "Al insertar un segundo elemento en la lista, el tamaño es dos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e2, "El elemento insertado está en posición 1");

	lista_insertar_en_posicion(lista, e3, 1);

	pa2m_afirmar(lista_tamanio(lista) == 3, "Al insertar arbitrariamente un tercer elemento, el tamaño es 3");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e3, "El elemento insertado en la posición arbitraria fue insertado correctamente");

	lista_insertar_en_posicion(lista, e4, 0);

	pa2m_afirmar(lista_tamanio(lista) == 4, "Al insertar arbitrariamente un cuarto elemento, el tamaño es 4");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e4, "El elemento insertado en la posición 0 fue insertado correctamente");

	lista_insertar_en_posicion(lista, e5, 100);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == e5, "El quinto elemento insertado en una posición mayor a la de la cantidad de elementos fue insertado en la última posición");

	pa2m_afirmar(lista_primero(lista) == e4, "El primer elemento de la lista es correcto");
	pa2m_afirmar(lista_ultimo(lista) == e5, "El último elemento de la lista estáen posición 4 y es el correcto");

    lista_destruir(lista);

}

void QuitarDeLista(){
	lista_t* lista = lista_crear();

	void *e1 = (void*)0xaaa;
	void *e2 = (void*)0xbbb;
	void *e3 = (void*)0xccc;
	void *e4 = (void*)0x789;
	void *e5 = (void*)0xcafef00d;

	lista_insertar(lista, e1);
	lista_insertar(lista, e2);
	lista_insertar(lista, e3);
	lista_insertar(lista, e4);
	lista_insertar(lista, e5);

	pa2m_afirmar(lista_tamanio(lista) == 5, "Se insertan 5 elementos en la lista");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == e4, "El elemento de la cuarta posición es el correcto");

	lista_quitar(lista);

	pa2m_afirmar(lista_tamanio(lista) == 4, "Quitado un elemento, ahora hay 4 elementos");

	lista_quitar_de_posicion(lista, 1);

	pa2m_afirmar(lista_tamanio(lista) == 3, "Quitado un segundo elemento arbitrariamente, ahora hay 3 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e3, "El elemento en la posición en la que estaba el elemento quitado es el elemento correcto");

	lista_quitar_de_posicion(lista, 0);

	pa2m_afirmar(lista_tamanio(lista) == 2, "Quitado un tercer elemento arbitrariamente en la posición 0, ahora hay 2 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e3, "El elemento en la posición quitada es el correcto");

	lista_quitar_de_posicion(lista, 100);

	pa2m_afirmar(lista_tamanio(lista)== 1, "Quitado un cuarto elemento arbitrariamente en una posición mayor a la cantidad de elementos quita el último de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e3, "El elemento en la posición 0 es el correcto");
	pa2m_afirmar(lista_primero(lista) == e3, "El primer elemento de la lista está en la posición 0 y es correcto");
	pa2m_afirmar(lista_ultimo(lista) == e3, "El último elemento de la lista está en la posición 0 y es correcto");

	lista_quitar(lista);

	pa2m_afirmar(lista_tamanio(lista) == 0, "Se quita el elemento restante y ahora hay 0 elementos");
	pa2m_afirmar(lista_vacia(lista), "La lista vuelve a estar vacía");
	
	lista_destruir(lista);
}



int main()
{
	lista_t* lista = NULL;

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Creación de Lista ========================");
	CrearLista(lista);

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Inserción y Buscado (simple y arbitraria) ========================");
	InsertarEnLista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Quitado y Buscado (simple y arbitraria) ========================");
	QuitarDeLista();


	return pa2m_mostrar_reporte();
}
