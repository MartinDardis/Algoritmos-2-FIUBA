#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;
struct nodo{
  void* dato;
  nodo_t* siguiente;
};

struct lista{
  nodo_t *primero;
  nodo_t *ultimo;
  size_t elementos;
};

struct lista_iter {
  lista_t *lista;
  nodo_t *anterior;
  nodo_t *actual;
};

//Implementaciones de uso interno del tda
nodo_t *crear_nodo(void){ //Uso interno del tda
  nodo_t *nuevo=malloc(sizeof(nodo_t));
  if (nuevo  ==  NULL)
    return NULL;
  (nuevo->siguiente)=NULL;
  return nuevo;
}
void *ver_nodo(nodo_t *actual){ //Uso Interno del tda
  return (actual->dato);
}

//Implementaciones de las firmas publicas
lista_t *lista_crear(void){
  lista_t *nueva = malloc(sizeof(lista_t));
  if(nueva  ==  NULL)
    return NULL;
  (nueva->primero) = NULL;
  (nueva->ultimo) = NULL;
  (nueva->elementos) = 0;
  return nueva;
}

bool lista_esta_vacia(const lista_t *lista){
  if ( (lista->primero)  ==  NULL)
    return true;
  return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
  nodo_t *nuevo = crear_nodo();
  if (nuevo  ==  NULL)
    return false;
  (nuevo->dato) = dato;
  if (lista_esta_vacia(lista)){
    (lista->primero) = nuevo;
    (lista->ultimo) = nuevo;
    (lista->elementos) = 1;
  }
  else{
    (nuevo->siguiente) = (lista->primero);
    (lista->primero) = nuevo;
    (lista->elementos)++;
  }
  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
  nodo_t *nuevo = crear_nodo();
  if (nuevo  ==  NULL)
    return false;
  (nuevo->dato) = dato;
  if (lista_esta_vacia(lista)){
    (lista->primero) = nuevo;
    (lista->ultimo) = nuevo;
    (lista->elementos) = 1;
  }
  else{
    nodo_t *ultimo = (lista->ultimo);
    (ultimo->siguiente) = nuevo;
    (lista->ultimo) = nuevo;
    (lista->elementos)++;
  }
  return true;
}

void *lista_borrar_primero(lista_t *lista){
  if(lista_esta_vacia(lista))
    return NULL;
  nodo_t *actual = (lista->primero);
  void* dato = (actual->dato);
  (lista->primero) = (actual->siguiente);
  (lista->elementos)--;
  if (lista_esta_vacia(lista)){
    (lista->primero) = NULL;
    (lista->ultimo) = NULL;
  }
  free(actual);
  return dato;
}

void *lista_ver_primero(const lista_t *lista){
  if(lista_esta_vacia(lista))
    return NULL;
  return ver_nodo(lista->primero);
}

void *lista_ver_ultimo(const lista_t* lista){
  if(lista_esta_vacia(lista))
    return NULL;
  return ver_nodo(lista->ultimo);
}

size_t lista_largo(const lista_t *lista){
  return (lista->elementos);
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
    while (!lista_esta_vacia(lista)) {
      if (destruir_dato  ==  NULL)
        lista_borrar_primero(lista);
      else
        destruir_dato(lista_borrar_primero(lista));
    }
    free(lista);
    return;
}


/* ITERADOR INTERNO */
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
  if(lista_esta_vacia(lista))
    return;
  nodo_t *actual = (lista->primero);
  while( visitar((actual->dato),extra) && actual!= NULL )
    actual=(actual->siguiente);
  return;
}
/* ITERADOR EXTERNO */


lista_iter_t *lista_iter_crear(lista_t *lista){
  lista_iter_t *nuevo = malloc(sizeof(lista_iter_t));
  if (nuevo  ==  NULL)
    return NULL;
  (nuevo->lista) = lista;
  (nuevo->anterior) = NULL;
  (nuevo->actual) = (lista->primero);
  return nuevo;
}

bool lista_iter_avanzar(lista_iter_t *iter){
  if (lista_iter_al_final(iter)){//Si no hay nodo siguiente al que estoy.
    return false;
  }
  nodo_t* proximo = (iter->actual);
  proximo=(proximo->siguiente);
  (iter->anterior) = (iter->actual);//nodo anterior es el actual
  (iter->actual) = proximo;//nodo actual es el siguiente
  return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
  nodo_t *actual = (iter->actual);
  if(lista_iter_al_final(iter))
    return NULL;
  return (actual->dato);
}

bool lista_iter_al_final(const lista_iter_t *iter){
  if( (iter->actual) == NULL)
    return true;
  return false;
}

void lista_iter_destruir(lista_iter_t *iter){
  free(iter);
  return;
}

bool iter_insertar_primero (lista_iter_t *iter,void* dato){
  bool inserto = lista_insertar_primero(iter->lista,dato);
  if (inserto){
    (iter->actual) = ((iter->lista)->primero);
    (iter->anterior) = NULL;// Redundate?
  }
  return inserto;
}
bool iter_insertar_ultimo (lista_iter_t *iter,void* dato){
  nodo_t* ultimo_viejo = ((iter->lista)->ultimo);
  bool inserto = lista_insertar_ultimo(iter->lista,dato);
  if (inserto){
    (iter->anterior) = ultimo_viejo;
    (iter->actual) = ((iter->lista)->ultimo);
  }
  return inserto;
}
bool iter_insertar_medio(lista_iter_t *iter,void* dato){
  lista_t *lista = (iter->lista);
  nodo_t *nuevo = crear_nodo();
  if (nuevo   ==   NULL)
    return false;
  (nuevo->dato) = dato;// guardo el dato
  nodo_t *nodo_anterior = (iter->anterior);//cargo nodo anterior
  (nuevo->siguiente) = (iter->actual);//Nodo siguiente es donde estoy
  (nodo_anterior->siguiente) = nuevo;//el siguiente al anterior es el nuevo
  (iter->actual) = nuevo;//Pongo el iter sobre el nuevo
  (lista->elementos)++;//agrego un elemento a la lista
  return true;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
  if (lista_esta_vacia((iter)->lista) || (iter->anterior)  ==  NULL)//Insertar en una lista vacia o iter en primer elemento
    return iter_insertar_primero(iter,dato);
  else if(lista_iter_al_final(iter))//Insertar sobre el ultimo elemento
    return iter_insertar_ultimo(iter,dato);
  return iter_insertar_medio(iter,dato);//insertar en el medio
}

void *lista_iter_borrar(lista_iter_t *iter){
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter))//Si la lista esta vacia
      return NULL;
    if( (iter->lista)->elementos  ==  1){// Si la lista tiene 1 solo elemento
      void* dato = lista_borrar_primero(iter->lista);
      (iter->actual) = NULL;
      return dato;
    }
    if((iter->anterior) == NULL){// Si el elemento es el primero
      void* dato = lista_borrar_primero(iter->lista);
      (iter->actual) = ((iter->lista)->primero);
      return dato;
    }
    void* dato=((iter->actual)->dato);
    nodo_t *nuevo_actual=((iter->actual)->siguiente);
    free((iter->actual));
    (iter->actual)=nuevo_actual;
    ((iter->anterior)->siguiente)=nuevo_actual;
    ((iter->lista)->elementos)--;
    return dato;
}
