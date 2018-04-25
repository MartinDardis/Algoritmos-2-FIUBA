/*      Martin Dardis     101608       Fiona González Lisella       */
/*                   Archivo: pruebas_alumno.c                      */

#include <stdlib.h>
#include <stdio.h>
#include "cola.h"
#include "testing.h"


void liberar_dato(void* dato){
  free(dato);
}

void romper_cola(){
  printf("-------- Romper la cola --------\n");
  cola_t *cola=NULL;
  print_test("** Crear Cola",(cola=cola_crear())!=NULL);
  print_test("** Ver primero en cola vacia",cola_ver_primero(cola)==NULL);
  print_test("** Desencolar cola vacia",cola_desencolar(cola)== NULL);
  cola_destruir(cola,NULL);

}
void crear_encolar_lote_destruir(){
  printf("-------- Crear, encolar lote y destruir una cola --------\n");
  cola_t* cola=NULL;
  print_test("** Crear Cola",(cola=cola_crear())!=NULL);
  print_test("** Cola esta esta vacia", cola_esta_vacia(cola));
  for(int i=0;i<10;i++){
    char* numero_dinamico=malloc(sizeof(char));
    print_test("** Encolar",cola_encolar(cola,numero_dinamico));
  }
  print_test("** Cola esta no esta vacia", cola_esta_vacia(cola)==false);
  printf("** Destruir cola\n");
  cola_destruir(cola,liberar_dato);
}

void crear_encolar_varios_destruir(){
  printf("-------- Crear, encolar varios, Desencolar y destruir una cola --------\n");
  cola_t* cola=NULL;
  int vector[9]={1,2,3,4,5,6,7,8,9};
  print_test("** Crear Cola",(cola=cola_crear())!=NULL);
  print_test("** Cola esta esta vacia", cola_esta_vacia(cola));
  for(int i=0; i<9 ;i++){
    print_test("** Encolar",cola_encolar(cola,&vector[i]));
  }
  print_test("** Cola esta no esta vacia", cola_esta_vacia(cola)==false);
  print_test("** Primer elemento es primer dato",cola_ver_primero(cola) == &vector[0]);
  printf("** Primer dato es %i = %i\n",vector[0],*((int*)cola_ver_primero(cola)));
  for(int i=0 ; i < 9; i++)
  	print_test("** Desencolar",cola_desencolar(cola) == &vector[i]);
  cola_destruir(cola,NULL);
  print_test("** Cola esta vacia",cola_esta_vacia(cola));

}

void crear_encolar_uno_destruir(){
  printf("-------- Crear, encolar uno, desencolar y destruir una cola --------\n");
  cola_t* cola=NULL;
  double numero=14560;
  print_test("** Crear Cola",(cola=cola_crear())!=NULL);
  print_test("** Cola esta vacia",cola_esta_vacia(cola));
  print_test("** Encolar",cola_encolar(cola,&numero));
  print_test("** Cola esta no esta vacia", cola_esta_vacia(cola)==false);
  print_test("** Primer elemento es primer dato",cola_ver_primero(cola) == &numero);
  print_test("** Desencolar",cola_desencolar(cola)== &numero);
  cola_destruir(cola,NULL);
  print_test("** Cola esta vacia",cola_esta_vacia(cola));
}

void pruebas_cola_alumno(){

  crear_encolar_uno_destruir();
  crear_encolar_varios_destruir();
  crear_encolar_lote_destruir();
  romper_cola();
  printf("Total de errores %i\n",failure_count());
}
