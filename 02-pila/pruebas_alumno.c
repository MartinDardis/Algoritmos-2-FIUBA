/*      Martin Dardis     101608       Fiona González Lisella       */
/*                  Archivo: pruebas_alumno.c                       */
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void apilar_desapilar_lote_elemento(){
  pila_t* pila=NULL;
  pila=pila_crear();
  print_test("Crear Pila",pila!=NULL);
  printf("Apilando lote elementos \n");
  int elementos[21]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
  for (int i=0;i<21;i++){
    print_test("     Apilar",pila_apilar(pila,&elementos[i]));
  }
  print_test("Pila NO esta vacia",!pila_esta_vacia(pila));
  print_test("Desapilar ultimo",*((int*)pila_desapilar(pila))==elementos[20]);
  print_test("Desapilar ultimo",*((int*)pila_desapilar(pila))==elementos[19]);
  printf("Desapilar Todo\n");
  for (int i=18;i>=0;i--){
    print_test("  Desapilar",*((int*)pila_desapilar(pila))==elementos[i]);
  }
  print_test("Pila esta vacia",pila_esta_vacia(pila));
  pila_destruir(pila);
}

void apilar_desapilar_varios_elemento(){
   pila_t* pila=NULL;
   pila=pila_crear();
   print_test("Crear Pila",pila!=NULL);
   printf("Apilando varios elementos \n");
   int elemntos[5]={1,2,3,4,5};
   for (int i=0;i<5;i++){
     print_test("     Apilar",pila_apilar(pila,&elemntos[i]));
   }
   print_test("Desapilar ultimo",*((int*)pila_desapilar(pila))==elemntos[4]);
   print_test("Desapilar ultimo",*((int*)pila_desapilar(pila))==elemntos[3]);
   pila_destruir(pila);
 }

void apilar_desapilar_un_elemento(){
  pila_t* pila=NULL;
  pila=pila_crear();
  print_test("Crear Pila",pila!=NULL);
  int elem_1=1;
  print_test("Apilar",pila_apilar(pila,&elem_1));
  print_test("Desapilar",*((int*)pila_desapilar(pila))==elem_1);
  pila_destruir(pila);
}

void crear_apilar_ver(){
  pila_t* pila=NULL;
  int elem_1=1,elem_2=3,elem_3=5;
  printf("\n Apilar y ver tope:\n");
  pila=pila_crear();
  print_test("  Crear Pila",pila!=NULL);
  print_test("  Pila esta vacia",pila_esta_vacia(pila));
  print_test("  Apilar elemento",pila_apilar(pila,&elem_1));
  print_test("  Apilar elemento",pila_apilar(pila,&elem_2));
  print_test("  Apilar elemento",pila_apilar(pila,&elem_3));
  print_test("  Ver Tope de pila",*((int*)pila_ver_tope(pila))==elem_3);
  pila_destruir(pila);
  return;
}

bool crear_y_eliminar(){
  pila_t* pila=NULL;
  pila=pila_crear();
  print_test("    Crear Pila",pila!=NULL);
  pila_destruir(pila);
  return true;
}

void romper_pila(){
  pila_t* pila=NULL;
  pila=pila_crear();
  print_test("    Crear Pila",pila!=NULL);
  print_test("    Ver Tope Pila Vacia da NULL",pila_ver_tope(pila)==NULL);
  print_test("    Desapilar Pila Vacia da NULL",pila_desapilar(pila)==NULL);
  print_test("    Apilado de elemento NULL",pila_apilar(pila,NULL));
  print_test("    Desapilar Pila Vacia da NULL", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    print_test("Crear y eliminar pila", crear_y_eliminar());
    printf("\n ********* Rompimiento de la pila *********\n");
    romper_pila();
    printf("\n ********* Apilado y ver tope *********\n");
    crear_apilar_ver();
    printf("\n ********* Apilado y desapilado un elemento *********\n");
    apilar_desapilar_un_elemento();
    printf("\n ********* Apilado y desapilado varios elementos *********\n");
    apilar_desapilar_varios_elemento();
    printf("\n ********* Apilado y desapilado lote de elementos *********\n");
    apilar_desapilar_lote_elemento();
    printf("\n \n Total de errores %i\n\n",failure_count());
}
