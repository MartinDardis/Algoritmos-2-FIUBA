/*      Martin Dardis     101608       Fiona González Lisella       */
/*                   Archivo: Pila.c                                */

#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};
 /******************************************************************/

bool redimensionar(pila_t *pila,size_t tam){
  void* *datos_nuevos=realloc(pila->datos,tam * sizeof(void*));
  if (*datos_nuevos==NULL)
    return false;
  pila->datos=datos_nuevos;
  pila->capacidad=tam;
  return true;

}
bool verificar_tam(pila_t *pila){
  if( pila->cantidad == pila->capacidad){
    size_t nuevo_tam=0;
    nuevo_tam=(pila->capacidad)*2;
    if (!redimensionar(pila,nuevo_tam))
      return false;
  }
  else if(((pila->cantidad)*4 <= (pila->capacidad))&&(pila->capacidad >10)){
    size_t nuevo_tam=0;
    nuevo_tam=(pila->capacidad)/2;
    if (!redimensionar(pila,nuevo_tam))
      return false;
  }
  return true;
}

 /* *****************************************************************
  *                    PRIMITIVAS DE LA PILA
  * *****************************************************************/
pila_t* pila_crear(void){
    pila_t *pila=malloc(sizeof(pila_t));
    if(pila==NULL)
      return NULL;
    pila->capacidad=10;
    pila->cantidad=0;
    pila->datos=malloc((pila->capacidad)*(sizeof(void*)));
    if(pila->datos==NULL){
      free (pila);
      return NULL;
    }

    return pila;
 }

void pila_destruir(pila_t *pila){
   free(pila->datos);
   free(pila);
   return;
}

bool pila_esta_vacia(const pila_t *pila){
    if(pila->cantidad == 0)
      return true;
    return false;
}

bool pila_apilar(pila_t *pila,void* valor){
    if(!verificar_tam(pila))
      return false;
    pila->datos[pila->cantidad]= (void*) valor;
    (pila->cantidad)++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
  if(pila->cantidad == 0)
    return NULL;
  return (pila->datos[(pila->cantidad)-1]);
}

void* pila_desapilar(pila_t *pila){
    if(pila->cantidad == 0)
      return NULL;
    (pila->cantidad)--;
    verificar_tam(pila);
    return pila->datos[pila->cantidad];
}
