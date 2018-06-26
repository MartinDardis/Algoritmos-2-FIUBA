#ifndef ABB_H
#define ABB_H

#define _POSIX_C_SOURCE 200809L //strdup
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pila.h"

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Primitivas del abb

/* Crea un arbol binario de busqueda
 * Pre: Recibe una funcion de comparacion que recive 2 strings y devuelve 0 si ambas son iguales
 * un numero negativo si la primera es menor a la segunda, y un numero positivo si la primera es
 * mayor a la segunda. Recibe la funcion que destruye al dato, o NULL si no se debe destruir
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda el conjunto de clave y dato en un nuevo nodo del arbol
 * Si la clave ya esta en el arbol reemplaza el dato. Si no esta, lo guarda en un nuevo nodo.
 * Devuelve true si guarda el valor, o false si no lo hace
 * (si no hay arbol o nu puedo alocar memora).
 * Pre: El arbol existe
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Devuelve el dato perteneciente a la clave y elimina el conjunto de clave y dato del arbol
 * Si esa clave no esta guardada en el arbol devuelve NULL, si lo esta elimina el nodo
 * y devuelve el dato que contiene.
 * Pre: El arbol existe
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Devuelve el dato perteneciente a la clave en el arbol
 * Si esa clave no esta guardada en el arbol devuelve NULL, si lo esta devuelve
 * el dato que contiene, sin eliminar el nodo.
 * Pre: El arbol existe
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Devuelve true si la clave esta guardada en el arbol, o false si no lo esta
 * Pre: El arbol existe
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de claves que estan guardadas en el arbol
 * Pre: El arbol existe
 */
size_t abb_cantidad(abb_t *arbol);

/* Destruye un arbol binario de busqueda, y todos sus nodos
 * Pre: El arbol existe
 */
void abb_destruir(abb_t *arbol);

//iterador interno

/* Llama a una funcion visitar para todos los nodos del arbol en un recorriido
 * ordenado segun la funcion de comparacion. Se detiene si la funcion visitar
 * devuelve false.
 * Pre: El arbol existe
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

void abb_in_order_desde_hasta(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, const char* desde, const char* hasta);

//iterador externo


/* Crea un iterador externo del arbol binario, que recorre de forma ordenada segun
 * la funcion de comparacion.
 * Pre: El arbol existe
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Avanza a la siguiente posicion en un recorrido ordenado segun la funcion de comparacion.
 * Pre: El iterador externo existe
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Devuelve la clave del nodo actual del arbol, o NULL si no hay nodo actual
 * Pre: El iterador externo existe
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Devuelve true si el iterador ya finalizo el recorrido, o false en caso contrario
 * Pre: El iterador externo existe
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/* Destruye al iterador externo
 * Pre: El iterador externo existe
 */
void abb_iter_in_destruir(abb_iter_t* iter);

#endif
