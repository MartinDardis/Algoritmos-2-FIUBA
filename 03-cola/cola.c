/*      Martin Dardis     101608       Fiona González Lisella       */
/*                   Archivo: cola.c                                */
#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>

struct nodo;
typedef struct nodo nodo_t;

struct nodo{
  void* dato;
  nodo_t *siguiente;
};

struct cola{
  nodo_t *primero;
  nodo_t *ultimo;
};

cola_t* cola_crear(void){
  cola_t *cola=malloc(sizeof(cola_t));
  if (cola == NULL)
    return NULL;
  cola->primero=NULL;
  cola->ultimo=NULL;
  return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
  while (!cola_esta_vacia(cola)){
    void* dato_a_eliminar=cola_desencolar(cola);
    if(destruir_dato != NULL)
      destruir_dato(dato_a_eliminar);
  }
  free(cola);
  cola=NULL;
}

bool cola_esta_vacia(const cola_t *cola){
  if ((cola->primero) == NULL)
    return true;
  return false;
}

bool cola_encolar(cola_t *cola, void* valor){
  nodo_t *nodo_nuevo=malloc(sizeof(nodo_t));
  if (nodo_nuevo == NULL)
    return false;
  nodo_nuevo->dato=valor;//Guardo el dato en el nuevo nodo
  nodo_nuevo->siguiente=NULL;//El nodo siguiente es NULL
  if (cola->primero == NULL) { //si esta vacia
    cola->primero=nodo_nuevo;
    cola->ultimo=nodo_nuevo;
  }
  else {//si NO esta vacia
    nodo_t *ultimo_nodo=cola->ultimo;//Cargo el ultimo nodo
    ultimo_nodo->siguiente=nodo_nuevo;//Apunto el siguiente al nuevo nodo
    cola->ultimo=nodo_nuevo;//pongo el nuevo nodo como ultimo de la fila
  }
  return true;
}

void* cola_ver_primero(const cola_t *cola){
  if(cola->primero == NULL)
    return NULL;
  nodo_t *primer_nodo=cola->primero;
  return (primer_nodo->dato);
}

void* cola_desencolar(cola_t *cola){
  if(cola->primero == NULL)
    return NULL;
  nodo_t *primer_nodo=cola->primero;
  void* dato_del_nodo=primer_nodo->dato;
  cola->primero=primer_nodo->siguiente;
  if(cola->primero==NULL)
    cola->ultimo=NULL;
  free(primer_nodo);
  return dato_del_nodo;
}
