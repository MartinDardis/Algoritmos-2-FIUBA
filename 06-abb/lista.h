#ifndef lista_H
#define lista_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void* valor);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void* valor);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Pre: lista esta creada y no esta vacia
// Destruye el primer nodo y actualiza la posicion inicial de la lista
void* lista_borrar_primero(lista_t* lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);

// Devuelve el largo
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*));

/* ******************************************************************
 *                    PRIMITIVAS DE ITERADORES
 * *****************************************************************/

// aplica una funcion externa en cada elemento de la lista
// pre: lista fue creada, la funcion pasada por parametro existe
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

typedef struct lista_iter lista_iter_t;

// Crea un iterador externo para una lista
// pre: la lista fue creada
lista_iter_t *lista_iter_crear(lista_t *lista);

// posiciona al iterador en la siguiente ubicacion de la lista
// pre: el iterador fue creado
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve la direccion del dato del elemento apuntado por el iterador
// o devuelve NULL si no puede
// pre: el iterador fue creado
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador se encuentra al final de la lista
// y false en caso contrario
// pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter);

// destruye el iterador
// pre: el iterador fue creado
void lista_iter_destruir(lista_iter_t *iter);

// inserta un elemento en la direccion de la lista a la cual apunta
// el iterador, devuelve true si puede hacerlo, y false si no puede
// pre: el iterador fue creado
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento de la lista apuntado por el iterador
// y devuelve la direccion del dato al que apunta. Si no puede devuelve NULL
// pre: el iterador fue creado
void *lista_iter_borrar(lista_iter_t *iter);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // lista_H
