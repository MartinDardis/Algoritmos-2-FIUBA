#define _POSIX_C_SOURCE 200809L //strdup
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pila.h"

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

typedef struct nodo_abb{
    char* clave;
    void* dato;
    struct nodo_abb* hijo_izq;
    struct nodo_abb* hijo_der;
} nodo_abb_t;

typedef struct abb{
    nodo_abb_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cantidad;
} abb_t;

// Primitivas del abb

/* Crea un nodo del arbol binario de busqueda con la clave y el dato recibidos
 */
nodo_abb_t* nodo_abb_crear(const char *clave, void *dato){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if(!nodo){
        return NULL;
    }
    nodo->clave = strdup(clave);
    nodo->dato = dato;
    nodo->hijo_izq = NULL;
    nodo->hijo_der = NULL;
    return nodo;
}

/* Destruye un nodo de un arbol binario de busqueda, si el arbol tiene una
 * funcion para destruir datos la llama.
 * Pre: El arbol existe
 */
void* nodo_abb_destruir(abb_t *arbol, nodo_abb_t* nodo){
    void* dato = nodo->dato;
    if(arbol->destruir_dato){
        arbol->destruir_dato(nodo->dato);
    }
    free(nodo->clave);
    free(nodo);
    return dato;
}

/* Crea un arbol binario de busqueda
 * Pre: Recibe una funcion de comparacion que recive 2 strings y devuelve 0 si ambas son iguales
 * un numero negativo si la primera es menor a la segunda, y un numero positivo si la primera es
 * mayor a la segunda. Recibe la funcion que destruye al dato, o NULL si no se debe destruir
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* arbol = malloc(sizeof(abb_t));
    arbol->raiz = NULL;
    arbol->cmp = cmp;
    arbol->destruir_dato = destruir_dato;
    arbol->cantidad = 0;
    return arbol;
}

/* Devuelve recursivamente a cada nodo del arbol binario de busqueda, en un
 * recorrido posorder
 * Pre: El arbol existe
 */
void abb_destruir_recursivo(abb_t *arbol, nodo_abb_t* nodo_actual){
    if(!nodo_actual){
        return;
    }
    abb_destruir_recursivo(arbol, nodo_actual->hijo_izq);
    abb_destruir_recursivo(arbol, nodo_actual->hijo_der);
    nodo_abb_destruir(arbol, nodo_actual);
    return;
}

/* Destruye un arbol binario de busqueda, y todos sus nodos
 * Pre: El arbol existe
 */
void abb_destruir(abb_t *arbol){
    abb_destruir_recursivo(arbol, arbol->raiz);
    free(arbol);
}

/* Busca al nodo que contiene la clave recibida.
 * Devuelve al nodo, o NULL si no lo encuentra, y actualiza la
 * posicion del padre de ese nodo
 * Pre: El arbol existe
 */
nodo_abb_t* nodo_buscar(const abb_t *arbol, nodo_abb_t** padre, const char *clave_buscada){
    *padre = NULL;
    nodo_abb_t* nodo_actual = arbol->raiz;

    bool encontro = false;
    int comparacion;
    while((nodo_actual) && (!encontro)){
        comparacion = arbol->cmp(clave_buscada, nodo_actual->clave);
        if(comparacion == 0){
            encontro = true;
        } else {
            *padre = nodo_actual;
            if(comparacion < 0){
                nodo_actual = nodo_actual->hijo_izq;
            } else {
                nodo_actual = nodo_actual->hijo_der;
            }
        }
    }
    return nodo_actual;
}

/* Reemplaza el dato contenido en un nodo, llamando a la funcion de destruir
 * dato si es que el arbol tiene una
 * Pre: El arbol existe
 */
void reemplazar_dato(abb_t* arbol, nodo_abb_t* nodo, void* dato){
    if(arbol->destruir_dato){
        arbol->destruir_dato(nodo->dato);
    }
    nodo->dato = dato;
}

/* Reemplaza el dato y la clave de 2 nodos recibidos
 * Pre: Ambos nodos existen
 */
void reemplazar_nodo(nodo_abb_t* nodo1, nodo_abb_t* nodo2){
    char* clave_aux = nodo1->clave;
    void* dato_aux = nodo1->dato;
    nodo1->clave = nodo2->clave;
    nodo1->dato = nodo2->dato;
    nodo2->clave = clave_aux;
    nodo2->dato = dato_aux;
}

/* Guarda el conjunto de clave y dato en un nuevo nodo del arbol
 * Si la clave ya esta en el arbol reemplaza el dato. Si no esta, lo guarda en un nuevo nodo.
 * Devuelve true si guarda el valor, o false si no lo hace
 * (si no hay arbol o nu puedo alocar memora).
 * Pre: El arbol existe
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo = nodo_buscar(arbol, &padre, clave);

    if(nodo){
        reemplazar_dato(arbol, nodo, dato);
        return true;
    }

    if(!padre){
        arbol->raiz = nodo_abb_crear(clave, dato);
        if(!arbol->raiz){
            return false;
        }
        arbol->cantidad++;
        return true;
    }

    int comparacion = arbol->cmp(clave, padre->clave);
    if(comparacion < 0){
        padre->hijo_izq = nodo_abb_crear(clave, dato);
        if(!padre->hijo_izq){
            return false;
        }
        arbol->cantidad++;
    } else {
        padre->hijo_der = nodo_abb_crear(clave, dato);
        if(!padre->hijo_der){
            return false;
        }
        arbol->cantidad++;
    }
    return true;
}

/* Destruye un nodo sin hijos y devuelve su dato
 * Pre: el arbol existe, la clabe pertenece al nodo a borrar, el nodo a borrar existe
 * y no tiene ningun hijo
 */
void* abb_borrar_nodo_sin_hijos(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t* padre){
    if(!padre){ //borro la raiz
        arbol->raiz = NULL;
        return nodo_abb_destruir(arbol, nodo_a_borrar);
    }

    if(padre->hijo_izq == nodo_a_borrar){
        padre->hijo_izq = NULL;
    } else {
        padre->hijo_der = NULL;
    }

    return nodo_abb_destruir(arbol, nodo_a_borrar);
}

/* Destruye un nodo con 1 hijo y devuelve su dato
 * Pre: el arbol existe, la clabe pertenece al nodo a borrar, el nodo a borrar existe
 * y tiene 1 solo hijo
 */
void* abb_borrar_nodo_con_1_hijo(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t* padre){
    if(!padre){ //borro la raiz
        if(nodo_a_borrar->hijo_izq != NULL){
            arbol->raiz = nodo_a_borrar->hijo_izq;
        } else {
            arbol->raiz = nodo_a_borrar->hijo_der;
        }
        return nodo_abb_destruir(arbol, nodo_a_borrar);
    }

    if(padre->hijo_izq == nodo_a_borrar){
        if(nodo_a_borrar->hijo_izq){
            padre->hijo_izq = nodo_a_borrar->hijo_izq;
        } else {
            padre->hijo_izq = nodo_a_borrar->hijo_der;
        }
    } else{
        if(nodo_a_borrar->hijo_izq){
            padre->hijo_der = nodo_a_borrar->hijo_izq;
        } else {
            padre->hijo_der = nodo_a_borrar->hijo_der;
        }
    }
    return nodo_abb_destruir(arbol, nodo_a_borrar);
}

/* Destruye un nodo con 2 hijos y devuelve su dato
 * Pre: el arbol existe, la clabe pertenece al nodo a borrar, el nodo a borrar existe
 * y tiene 2 hijos
 */
void* abb_borrar_nodo_con_2_hijos(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t* padre){
    nodo_abb_t* padre_del_reemplazante = nodo_a_borrar;
    nodo_abb_t* reemplazante = (nodo_a_borrar->hijo_der);
    while(reemplazante->hijo_izq){
        padre_del_reemplazante = reemplazante;
        reemplazante = reemplazante->hijo_izq;
    }

    reemplazar_nodo(nodo_a_borrar, reemplazante);
    if(reemplazante->hijo_der){
        return  abb_borrar_nodo_con_1_hijo(arbol, clave, reemplazante, padre_del_reemplazante);
    } else {
        return  abb_borrar_nodo_sin_hijos(arbol, clave, reemplazante, padre_del_reemplazante);
    }
}

/* Devuelve el dato perteneciente a la clave y elimina el conjunto de clave y dato del arbol
 * Si esa clave no esta guardada en el arbol devuelve NULL, si lo esta elimina el nodo
 * y devuelve el dato que contiene.
 * Pre: El arbol existe
 */
void *abb_borrar(abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo_a_borrar = nodo_buscar(arbol, &padre, clave);
    if(!nodo_a_borrar){
        return NULL;
    }

    arbol->cantidad--;

    if (!nodo_a_borrar->hijo_izq && !nodo_a_borrar->hijo_der){
        return abb_borrar_nodo_sin_hijos(arbol, clave, nodo_a_borrar, padre);
    }
    if (!nodo_a_borrar->hijo_izq || !nodo_a_borrar->hijo_der){
        return abb_borrar_nodo_con_1_hijo(arbol, clave, nodo_a_borrar, padre);
    }
    return abb_borrar_nodo_con_2_hijos(arbol, clave, nodo_a_borrar, padre);
}

/* Devuelve el dato perteneciente a la clave en el arbol
 * Si esa clave no esta guardada en el arbol devuelve NULL, si lo esta devuelve
 * el dato que contiene, sin eliminar el nodo.
 * Pre: El arbol existe
 */
void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo = nodo_buscar(arbol, &padre, clave);
    if(nodo == NULL){
        return NULL;
    }

    return nodo->dato;
}

/* Devuelve true si la clave esta guardada en el arbol, o false si no lo esta
 * Pre: El arbol existe
 */
bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    return nodo_buscar(arbol, &padre, clave) != NULL;
}

/* Devuelve la cantidad de claves que estan guardadas en el arbol
 * Pre: El arbol existe
 */
size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}


//iterador interno

/* Llama a una funcion visitar para todos los nodos del arbol en un recorriido
 * ordenado segun la funcion de comparacion. Se detiene si la funcion visitar
 * devuelve false.
 * Pre: El arbol existe
 */
void abb_in_order_recursivo(nodo_abb_t* nodo, bool visitar(const char *, void *, void *), void *extra, bool* iterar){
    if(!nodo){
        return;
    }
    if(*iterar){
        abb_in_order_recursivo(nodo->hijo_izq, visitar, extra, iterar);
    }
    if(*iterar){
        *iterar = visitar(nodo->clave, nodo->dato, extra);
    }
    if(*iterar){
        abb_in_order_recursivo(nodo->hijo_der, visitar, extra, iterar);
    }
    return;
}

/* Llama a una funcion visitar para todos los nodos del arbol en un recorriido
 * ordenado segun la funcion de comparacion. Se detiene si la funcion visitar
 * devuelve false.
 * Pre: El arbol existe
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    bool iterar = true;
    abb_in_order_recursivo(arbol->raiz, visitar, extra, &iterar);
}


//iterador externo

typedef struct abb_iter{
    const abb_t* arbol;
    pila_t* pila;
}abb_iter_t;

/* Crea un iterador externo del arbol binario, que recorre de forma ordenada segun
 * la funcion de comparacion.
 * Pre: El arbol existe
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter){
        return NULL;
    }
    iter->pila = pila_crear();
    if(!iter->pila){
        free(iter);
        return NULL;
    }

    iter->arbol = arbol;
    nodo_abb_t* nodo_actual = iter->arbol->raiz;
    while(nodo_actual){
        pila_apilar(iter->pila, nodo_actual);
        nodo_actual = nodo_actual->hijo_izq;
    }
    return iter;
}

/* Avanza a la siguiente posicion en un recorrido ordenado segun la funcion de comparacion.
 * Pre: El iterador externo existe
 */
bool abb_iter_in_avanzar(abb_iter_t *iter){
    nodo_abb_t* nodo_actual = pila_desapilar(iter->pila);
    if(!nodo_actual){
        return false;
    }

    nodo_actual = nodo_actual->hijo_der;
    while(nodo_actual){
        pila_apilar(iter->pila, nodo_actual);
        nodo_actual = nodo_actual->hijo_izq;
    }
    return true;
}

/* Devuelve la clave del nodo actual del arbol, o NULL si no hay nodo actual
 * Pre: El iterador externo existe
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    nodo_abb_t* nodo_actual = pila_ver_tope(iter->pila);
    if(!nodo_actual){
        return NULL;
    }

    return nodo_actual->clave;
}

/* Devuelve true si el iterador ya finalizo el recorrido, o false en caso contrario
 * Pre: El iterador externo existe
 */
bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

/* Destruye al iterador externo
 * Pre: El iterador externo existe
 */
void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}
