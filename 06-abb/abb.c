#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

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

// lo tuve que sacar de internet porque el -std=c99 no me dejaba usar strdup
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

// Primitivas del abb < > ->, me escribi eso por si queria copiar y pegar

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

void* nodo_abb_destruir(abb_t *arbol, nodo_abb_t* nodo){
    void* dato = nodo->dato;
    if(arbol->destruir_dato){
        arbol->destruir_dato(nodo->dato);
    }
    free(nodo->clave);
    free(nodo);
    return dato;
}

//
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* arbol = malloc(sizeof(abb_t));
    arbol->raiz = NULL;
    arbol->cmp = cmp;
    arbol->destruir_dato = destruir_dato;
    arbol->cantidad = 0;
    return arbol;
}

//
void abb_destruir_recursivo(abb_t *arbol, nodo_abb_t* nodo_actual){
    if(!nodo_actual){
        return;
    }
    abb_destruir_recursivo(arbol, nodo_actual->hijo_izq);
    abb_destruir_recursivo(arbol, nodo_actual->hijo_der);
    nodo_abb_destruir(arbol, nodo_actual);
    return;
}

//
void abb_destruir(abb_t *arbol){
    abb_destruir_recursivo(arbol, arbol->raiz);
    free(arbol);
}

//
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

void reemplazar_dato(abb_t* arbol, nodo_abb_t* nodo, void* dato){
    if(arbol->destruir_dato){
        arbol->destruir_dato(nodo->dato);
    }
    nodo->dato = dato;
}

void reemplazar_nodo(abb_t* arbol, nodo_abb_t* nodo, char* clave, void* dato){
    if(arbol->destruir_dato){
        arbol->destruir_dato(nodo->dato);
    }
    nodo->dato = dato;
    free(nodo->clave);
    nodo->clave = clave;
}
//
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

void* abb_borrar_nodo_con_1_hijo(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t* padre){
    if(!padre){ //borro la raiz
        if(nodo_a_borrar->hijo_izq != NULL){
            arbol->raiz = nodo_a_borrar->hijo_izq;
        } else {
            arbol->raiz = nodo_a_borrar->hijo_der;
        }
        return nodo_abb_destruir(arbol, nodo_a_borrar);
    }

    if(padre->hijo_izq){
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

/*nodo_abb_t* buscar_reemplazante(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t** padre_del_reemplazante){
    nodo_abb_t* nodo_actual = nodo_a_borrar->hijo_der;
    *padre_del_reemplazante = nodo_a_borrar;

    while(nodo_actual->hijo_izq){
        *padre_del_reemplazante = nodo_actual;
        nodo_actual = nodo_actual->hijo_izq;
    }

    return nodo_actual;
}*/

void* abb_borrar_nodo_con_2_hijos(abb_t *arbol, const char *clave, nodo_abb_t* nodo_a_borrar, nodo_abb_t* padre){
    nodo_abb_t* padre_del_reemplazante = nodo_a_borrar;
    nodo_abb_t* reemplazante = (nodo_a_borrar->hijo_der);
    while(reemplazante->hijo_izq){
        padre_del_reemplazante = reemplazante;
        reemplazante = reemplazante->hijo_izq;
    }

    void* dato_nuevo;
    char* clave_nueva = strdup(reemplazante->clave);//para no llamar a abb_borrar y que lo busque de nuevo
    if(reemplazante->hijo_der){
        dato_nuevo = abb_borrar_nodo_con_1_hijo(arbol, clave_nueva, reemplazante, padre_del_reemplazante);
    } else {
        dato_nuevo = abb_borrar_nodo_sin_hijos(arbol, clave_nueva, reemplazante, padre_del_reemplazante);
    }

    void* dato_auxiliar = nodo_a_borrar->dato;
    reemplazar_nodo(arbol, nodo_a_borrar, clave_nueva, dato_nuevo);
    return dato_auxiliar;
}

//
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

//
void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo = nodo_buscar(arbol, &padre, clave);
    if(nodo == NULL){
        return NULL;
    }

    return nodo->dato;
}

//
bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    return nodo_buscar(arbol, &padre, clave) != NULL;
}

//
size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}


//iterador interno
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

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    bool iterar = true;
    abb_in_order_recursivo(arbol->raiz, visitar, extra, &iterar);
}

//iterador externo

typedef struct abb_iter{
    const abb_t* arbol;
    lista_t* lista;
}abb_iter_t;

void abb_iter_in_destruir(abb_iter_t* iter){
    free(iter->lista);
    free(iter);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter){
        return NULL;
    }
    iter->lista = lista_crear();
    if(!iter->lista){
        free(iter);
        return NULL;
    }

    iter->arbol = arbol;
    nodo_abb_t* nodo_actual = iter->arbol->raiz;
    while(nodo_actual){
        lista_insertar_primero(iter->lista, nodo_actual);
        nodo_actual = nodo_actual->hijo_izq;
    }
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    nodo_abb_t* nodo_actual = lista_borrar_primero(iter->lista);
    if(!nodo_actual){
        return false;
    }

    nodo_actual = nodo_actual->hijo_der;
    while(nodo_actual){
        lista_insertar_primero(iter->lista, nodo_actual);
        nodo_actual = nodo_actual->hijo_izq;
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    nodo_abb_t* nodo_actual = lista_ver_primero(iter->lista);
    if(!nodo_actual){
        return NULL;
    }

    return nodo_actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return lista_esta_vacia(iter->lista);
}
