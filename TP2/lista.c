#include "lista.h"
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
typedef struct nodo{
    void* dato;
    struct nodo* proximo;
} nodo_t;

/* La lista está planteada como una lista de punteros genéricos. */
struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/
// Crea un nodo
// Post: Devuelve un nuevo nodo vacio, o NULL en caso de error
nodo_t* nodo_crear(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL){
        return NULL;
    }

    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

// Destruye el nodo, y hace llamado a una funcion pasada por parametro
// si se pasa alguna, usando el dato del nodo como parametro
void nodo_destruir(nodo_t* nodo, void destruir_dato(void*)){
    if(destruir_dato != NULL){
        destruir_dato(nodo->dato);
    }
    free(nodo);
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista == NULL){
        return NULL;
    }

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
    return (lista->primero == NULL); //REVISAR puede ser !lista->largo
}

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void* valor){
    nodo_t* nodo_nuevo = nodo_crear(valor);
    if(nodo_nuevo == NULL){
        return false;
    }

    if(lista_esta_vacia(lista)){
        lista->ultimo = nodo_nuevo;
    }
    nodo_t* nodo_auxiliar = lista->primero;
    lista->primero = nodo_nuevo;
    lista->primero->dato = valor;
    lista->primero->proximo = nodo_auxiliar;
    lista->largo++;
    return true;
}

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void* valor){
    nodo_t* nodo_nuevo = nodo_crear(valor);
    if(nodo_nuevo == NULL){
        return false;
    }

    if(lista_esta_vacia(lista)){
        lista->primero = nodo_nuevo;
    } else {
        lista->ultimo->proximo = nodo_nuevo;
    }
    lista->ultimo = nodo_nuevo;
    lista->largo++;
    return true;
}

// Pre: lista esta creada y no esta vacia
// Destruye el primer nodo y actualiza la posicion inicial de la lista
void lista_destruir_primero(lista_t* lista, void destruir_dato(void*)){
    nodo_t* segundo = lista->primero->proximo;
    nodo_destruir(lista->primero, destruir_dato);

    lista->primero = segundo;
    lista->largo--; //REVISAR, no se si va aca o en lista_borrar_primero
}

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return (lista->primero->dato);
}

// Pre: lista esta creada y no esta vacia
// Destruye el primer nodo y actualiza la posicion inicial de la lista
void* lista_borrar_primero(lista_t* lista){
    void* valor = lista_ver_primero(lista);
    if(!lista_esta_vacia(lista)){
        lista_destruir_primero(lista, NULL);
    }
    return valor;
}

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return (lista->ultimo->dato);
}

//
size_t lista_largo(const lista_t* lista){
    return lista->largo;
}

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*)){
    while(!lista_esta_vacia(lista)){
        lista_destruir_primero(lista, destruir_dato);
    }
    free(lista);
}

/* ******************************************************************
 *                          ITERADORES
 * *****************************************************************/

// aplica una funcion externa en cada elemento de la lista
// pre: lista fue creada, la funcion pasada por parametro existe
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    if(lista->primero == NULL){
        return;
    }

    nodo_t* actual = lista->primero;
    while(actual != NULL){
        if (!visitar(actual->dato, extra)){
            return;
        }
        actual = actual->proximo;
    }
}

struct lista_iter{
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
};

// Crea un iterador externo para una lista
// pre: la lista fue creada
lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(iter == NULL){
        return NULL;
    }

    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    return iter;
}

// Devuelve true si el iterador se encuentra al final de la lista
// y false en caso contrario
// pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

// Devuelve true si el iterador se encuentra al inicio de la lista
// y false en caso contrario
// pre: el iterador fue creado
bool lista_iter_al_principio(const lista_iter_t *iter){
    return iter->anterior == NULL;
}

// posiciona al iterador en la siguiente ubicacion de la lista
// pre: el iterador fue creado
bool lista_iter_avanzar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)){
        return false;
    }

    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;
    return true;
}

// Devuelve la direccion del dato del elemento apuntado por el iterador
// o devuelve NULL si no puede
// pre: el iterador fue creado
void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(lista_iter_al_final(iter)){
        return NULL;
    }
    return iter->actual->dato;
}

// inserta un elemento en la direccion de la lista a la cual apunta
// el iterador, devuelve true si puede hacerlo, y false si no puede
// pre: el iterador fue creado
bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* nodo_nuevo = nodo_crear(dato);
    if(nodo_nuevo == NULL){
        return false;
    }

    if(lista_iter_al_principio(iter)){
        nodo_t* nodo_auxiliar = iter->lista->primero;
        iter->lista->primero = nodo_nuevo;
        iter->lista->primero->proximo = nodo_auxiliar;
    } else {
        iter->anterior->proximo = nodo_nuevo;
        nodo_nuevo->proximo = iter->actual;

        if(lista_iter_al_final(iter)){
            iter->lista->ultimo->proximo = nodo_nuevo;
        }
    }

    if(lista_iter_al_final(iter)){
        iter->lista->ultimo = nodo_nuevo;
    }

    iter->actual = nodo_nuevo;
    iter->lista->largo++;
    return true;

}

// Elimina el elemento de la lista apuntado por el iterador
// y devuelve la direccion del dato al que apunta. Si no puede devuelve NULL
// pre: el iterador fue creado
void *lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)){
        return NULL;
    }

    nodo_t* nodo_a_borrar = iter->actual;
    void* valor = nodo_a_borrar->dato;

    if(iter->actual->proximo == NULL){
        iter->lista->ultimo = iter->anterior;
    }
    if(lista_iter_al_principio(iter)){
        iter->lista->primero = iter->actual->proximo;
    } else {
        iter->anterior->proximo = iter->actual->proximo;
    }

    iter->actual = iter->actual->proximo;
    iter->lista->largo--;
    free(nodo_a_borrar);
    return valor;
}

// destruye el iterador
// pre: el iterador fue creado
void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}
