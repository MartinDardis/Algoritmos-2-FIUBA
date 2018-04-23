#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "testing.h"


void prueba_iter_externo_insertar_varios_elementos(){
  printf("\n++++++ Insertar Varios elemento ++++++\n" );
  int vector[5]={1,2,3,4,5};
  lista_t *lista=lista_crear();
  lista_iter_t *iter=lista_iter_crear(lista);
  print_test("* Insertar en lista vacia", lista_iter_insertar(iter,&vector[0]));
  lista_iter_avanzar(iter);
  print_test("* Insertar en lista", lista_iter_insertar(iter,&vector[3]));
  lista_iter_avanzar(iter);
  printf("Actual es : %i \n",* (int*)(lista_iter_ver_actual(iter)));
  print_test("* Insertar en lista", lista_iter_insertar(iter,&vector[4]));
  printf("Actual es : %i \n",* (int*)(lista_iter_ver_actual(iter)));
  printf("* Lista ver ultimo %i\n",*(int*)lista_ver_ultimo(lista) );
}

void prueba_iter_externo_recorrer_varios_elementos(void){
  printf("\n++++++ recorrer Varios elemento ++++++\n" );
  lista_t *lista=lista_crear();
  int* vector[20];
  print_test ("* Preparando la lista",true);
  for(int i=0;i<20;i++){
    lista_insertar_ultimo(lista,vector[i]);
  }
  lista_iter_t *iter=lista_iter_crear(lista);
  print_test("* Iterador apuntando a primer elemento",lista_ver_primero(lista) == lista_iter_ver_actual(iter));
  print_test("* Iterador no esta al final",!lista_iter_al_final(iter));
  for(int i=1;i<20;i++){
    print_test("* Iterador avanzar",lista_iter_avanzar(iter));
    print_test("* Iterador es el elemento esperado",lista_iter_ver_actual(iter) == vector[i]);
  }
  print_test("* Iterador esta al final",lista_iter_al_final(iter));
  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  printf("\n++++++ Fin recorrer varios elemento ++++++\n" );
}


void prueba_iter_externos_1_elemento(void){
  printf("\n++++++ 1 elemento ++++++\n" );
  lista_t *lista=lista_crear();
  lista_iter_t *iter=lista_iter_crear(lista);
  int numero=1;
  print_test("* Lista vacia - Iterador apuntando a NULL",(lista_esta_vacia(lista)) && (lista_iter_ver_actual(iter)) == NULL);
  print_test("* Insertar con interador",lista_iter_insertar(iter,&numero));
  print_test("* Ver primero y iter ver actual",((lista_ver_primero(lista)) && (lista_iter_ver_actual(iter)) ));
  print_test("* Eliminar elemento y lista queda vacia",(lista_iter_borrar(iter) && lista_esta_vacia (lista) ));
  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  printf("\n++++++ Fin 1 elemento ++++++\n" );
}

void prueba_iter_externos(void){
  printf("\n++++++ Pruebas de las PRIMITIVAS de la iterador externo ++++++\n" );
  prueba_iter_externos_1_elemento();
  prueba_iter_externo_recorrer_varios_elementos();
  prueba_iter_externo_insertar_varios_elementos();
}

void primitivas_lista(void){
  printf("++++++ Pruebas de las PRIMITIVAS de la lista ++++++\n" );
  lista_t *lista=lista_crear();
  int numero=1;
  char vector[10];//={'a','b','c','d','e','f','g','h','i','j'};
  print_test("* Crear una lista",lista!=NULL);
  print_test("* Lista esta vacia",lista_esta_vacia(lista));
  print_test("* Insertar primero",lista_insertar_primero(lista,&numero));
  print_test("* Lista ver primero", (&numero == lista_ver_primero (lista) ) );
  print_test("* Ver primero = Ver ultimo",lista_ver_primero(lista)==lista_ver_ultimo(lista));
  print_test("* Largo de la lista es 1", lista_largo(lista)==1 );
  printf("++++++ Pruebas en volumen \n");
  printf("* El ultimo elemento a insertar es -> '%c'\n",vector[9] );
  for(int i=0;i<10;i++){
    print_test("** Insertar ultimo",lista_insertar_ultimo(lista,&vector[i]));
  }
  print_test("* Lista ver primero", (&numero == lista_ver_primero (lista) ) );
  printf("* El ultimo elemento es -> '%c'\n",*((char*)lista_ver_ultimo(lista)));
  lista_borrar_primero(lista);
  for(int i=0;i<10;i++){
    print_test("** Borrar primero",*((char*)lista_borrar_primero(lista)) == vector [i]) ;
  }
  lista_destruir(lista,NULL);

}

void pruebas_lista_alumno(void){
  primitivas_lista();
  prueba_iter_externos();

  printf("\n Total de errores %i\n",failure_count() );
  return;
}
