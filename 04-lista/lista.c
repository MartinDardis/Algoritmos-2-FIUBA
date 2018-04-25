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
  if ( (lista->primero)  ==  NULL )
    return true;
  return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
  nodo_t *nuevo = malloc(sizeof(nodo_t));
  if (nuevo  ==  NULL)
    return false;
  (nuevo->dato) = dato;
  (nuevo->siguiente) = (lista->primero);
  if (lista_esta_vacia(lista)){
    (lista->primero) = nuevo;
    (lista->ultimo) = nuevo;
  }
  else{
    (lista->primero) = nuevo;
  }
  (lista->elementos)++;
  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
  nodo_t *nuevo = malloc(sizeof(nodo_t));// creo el nodo
  if (nuevo  ==  NULL)
    return false;
  (nuevo->dato) = dato;// le guardo el dato
  (nuevo->siguiente) = NULL;//EL siguiente es NULL por ser el ultimo
  if (lista_esta_vacia(lista)){//Si no hay elementos
    (lista->primero) = nuevo;
    (lista->ultimo) = nuevo;
  }
  else{
    ((lista->ultimo)->siguiente) = nuevo;
    (lista->ultimo) = nuevo;
  }
      (lista->elementos)++;
  return true;
}

void *lista_borrar_primero(lista_t *lista){
  if(lista_esta_vacia(lista))
    return NULL;
  nodo_t *actual = (lista->primero);
  void* dato = (actual->dato);
  (lista->primero) = (actual->siguiente);
  (lista->elementos)--;
  if ((lista->primero) == NULL)
    (lista->ultimo) = NULL;
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
    lista=NULL;
    return;
}


/* ITERADOR INTERNO */
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
  if(lista_esta_vacia(lista))
    return;
  nodo_t *actual = (lista->primero);
  while((actual != NULL ) && visitar((actual->dato),extra) )
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
  iter=NULL;
  return;
}

bool iter_insertar_primero (lista_iter_t *iter,void* dato){
  if (lista_insertar_primero(iter->lista,dato)){
    (iter->actual) = ((iter->lista)->primero);
    (iter->anterior) = NULL;// Redundate?
    return true;
  }
  return false;
}
bool iter_insertar_ultimo (lista_iter_t *iter,void* dato){
  if(lista_insertar_ultimo(iter->lista,dato))
    (iter->actual)=((iter->lista)->ultimo);
  return true;
}
bool iter_insertar_medio(lista_iter_t *iter,void* dato){
  lista_t *lista = (iter->lista);
  nodo_t *nuevo = malloc(sizeof(nodo_t));
  if (nuevo   ==   NULL)
    return false;
  (nuevo->dato) = dato;// guardo el dato
  nodo_t *nodo_anterior = (iter->anterior);//cargo nodo anterior
  (nodo_anterior->siguiente) = nuevo;//el siguiente al anterior es el nuevo
  (nuevo->siguiente) = (iter->actual);//Nodo siguiente es donde estoy
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
  if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) // Casos en los que no hay nada que borrar
    return NULL;
  if((iter->anterior) == NULL || lista_largo(iter->lista) == 1){// Cuando el elemento es el primero o es unico
    void* dato = lista_borrar_primero(iter->lista);//borro el primer elemento
    (iter->actual) = ((iter->lista)->primero);//el nuevo actual es el NUEVO primero de la lista
    return dato;//devuelvo el dato
  }
  nodo_t* aux = (iter->actual);//Cargo nodo a borrar
  if((iter->actual)->siguiente == NULL){// Si es el ultimo elemento
    ((iter->anterior)->siguiente) = NULL;
    ((iter->lista)->ultimo) = (iter->anterior);
    (iter->actual) = NULL;
    ((iter->lista)->elementos)--;
    void* dato = (aux->dato);
    free(aux);
    return dato;
  }
  ((iter->anterior)->siguiente) = (aux->siguiente);//El siguiente de anterior es el siguiente del que voy a borrar
  (iter->actual) = (aux->siguiente);//Paro el iterador sobre el siguiente
  ((iter->lista)->elementos)--;//Resto un elemento a la lista
  void* dato_aux = (aux->dato);//saco el dato
  free(aux);//libero el nodo
  return dato_aux;//Devuelvo el dato
}
