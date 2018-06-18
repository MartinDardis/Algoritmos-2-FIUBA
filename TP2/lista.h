#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/*                   --- PRIMITIVAS DE LA LISTA ---                           */

//PRE: Ninguna
//POST: Si pudo crear devuelve la direccion de una lista vacio, sino devuelve NULL.
lista_t *lista_crear(void);

//PRE: lista debe ser creada
//POST: Devuelve TRUE si la lista no contiene elementos, sino devuelve FALSE.
bool lista_esta_vacia(const lista_t *lista);

//PRE: Lista debe ser creada.
//POST: Devuelve TRUE si pudo insertar el dato en la primer posicion y FALSE si
//      hubo un error.
bool lista_insertar_primero(lista_t *lista, void *dato);

//PRE: Lista debe ser creada.
//POST: Devuelve TRUE si pudo insertar el dato en la ultima posicion y FALSE si
//      hubo un error.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//PRE: Lista debe ser creada:
//POST: Si la lista contiene elementos devuelve el dato del primero elemento y
//      luego lo elimina. Si la lista esta vacia devuelve NULL.
void *lista_borrar_primero(lista_t *lista);

//PRE: Lista debe ser creada:
//POST: Si la lista contiene elementos devuelve el dato del primero elemento
//      la lista esta vacia devuelve NULL
void *lista_ver_primero(const lista_t *lista);

//PRE: Lista debe ser creada:
//POST: Si la lista contiene elementos devuelve el dato del ultimo elemento
//      la lista esta vacia devuelve NULL
void* lista_ver_ultimo(const lista_t* lista);

//PRE: Lista debe ser creada:
//POST: Devuelve la cantidad de elementos en la lista, siendo 0 si esta vacia.
size_t lista_largo(const lista_t *lista);

//PRE: Lista debe ser creada:
//POST: En caso de pasarle un puntero a funcion, envia el dato del elemento a
//      esta y luego elimina el elemento. La funcion PUEDE SER NULL, y de ser
//      asi solo eliminara los elementos sin importar los datos de los mismos.
void lista_destruir(lista_t *lista, void destruir_dato(void *));



/*                   --- PRIMITIVAS DE LOS ITERADORES ---                     */

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

//Dada una lista ya creada (puede estar vacia),devuelve un iterador para estar
//POST: Si no se pudo crear devuelve NULL sino devuelve un puntero
lista_iter_t *lista_iter_crear(lista_t *lista);

//Dado un lista_iter_t avanza al nodo siguiente al actual
//PRE: el iterador debe haber sido creado
//POST: devuelve TRUE si pudo avanzar y FALSE si no hay siguiente
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve el dato del elemento donde se encuentra apuntando el ITERADOR
//PRE: El iterador debe haber sido creado
//POST: Si esta en un elemento valido devuelve el dato sino devuelve NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Indica si el iterador esta poscionado sobre el ultimo elemento
//PRE: El iterdor debe haber sido creado
//POST: Se considera ultimo al ultimo elemento de la lista
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el ITERADOR
//Pre: el iterador debe haber sido creado
//POST: niguna.
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un elemento en la poscion actual del iterador. Si esta al principio insertar al
//principio de la lista. si esta al final inserta Ultimo y si esta en medio inserta corriendo el actual
// y dejandolo como siguiente
//PRE: el iterador debe haber sido creado.
//POST: Inserta un elemento, devolviendo true si inserto o false sino.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra un elemento de la lista. Si el elemento se encuentra en el medio de la lista
//Su siguiente pasa a ocupar su posicion
//PRE: el iterador debe haber sido creado
//POST: Devuelve el dato de el elemento eliminado.
void *lista_iter_borrar(lista_iter_t *iter);

#endif
