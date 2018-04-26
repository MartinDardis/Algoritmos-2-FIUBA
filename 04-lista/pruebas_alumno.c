#include  <stdlib.h>
#include  <stdio.h>
#include "lista.h"
#include "testing.h"
#define TAM_INSERTAR_ITERADOR 10
#define ELEMENTOS_A_INSERTAR {1,2,3,4,5,6,7,8,9,10}
#define TAM_VECTOR 10

void iter_ext_insertar_desordenado(){
   lista_t* lista = lista_crear();
   lista_iter_t* iter = lista_iter_crear(lista);
   int vector[3] = {1,2,3};
   print_test("* iter esta al final",lista_iter_al_final(iter));
   print_test("* Borrar lista vacio",!lista_iter_borrar(iter));
   print_test("* Avanzar iter lista vacia",!lista_iter_avanzar(iter));
   print_test("* Iter actual en lista vacia es NULL",lista_iter_ver_actual(iter)==NULL);
   print_test("* Inserto al principio",lista_iter_insertar(iter,&vector[0]));//meto al principio
   print_test("* Avanzo 1",lista_iter_avanzar(iter));
   print_test("* Iter esta al final",lista_iter_al_final(iter));
   print_test("* Inserto al final",lista_iter_insertar(iter,&vector[2]));//meto al final
   print_test("* Inserto al medio",lista_iter_insertar(iter,&vector[1]));//meto en el medio
   lista_iter_destruir(iter);
   iter = lista_iter_crear(lista);
   print_test("* Iter actual es 1",lista_iter_ver_actual(iter) == &vector[0]);
   print_test("* Iter borrar elemento",lista_iter_borrar(iter));
   print_test("* Iter actual es 2",lista_iter_ver_actual(iter) == &vector[1]);
   print_test("* Iter borrar elemento",lista_iter_borrar(iter));
   print_test("* Iter actual es 3",lista_iter_ver_actual(iter) == &vector[2]);
   print_test("* Iter borrar elemento",lista_iter_borrar(iter));
   print_test("* Lista esta vacia",lista_esta_vacia(lista));
   lista_iter_destruir(iter);
   lista_destruir(lista,NULL);
}

bool sumar_primeros_cinco(void* dato, void* extra){
  while( *(int*)extra < 15){
    *((int*)extra) += *((int*) dato);
    printf("contador %i\n", *(int*)extra );
    return true;
  }
  return false;
}

void prueba_iter_internos(){
  printf("\n++++++ Prueba iterador INTERNO ++++++\n" );
  lista_t* lista = lista_crear();
  print_test("* Crear una lista",!(lista == NULL));
  int vector[TAM_VECTOR] = ELEMENTOS_A_INSERTAR;
  for(int i=0; i < TAM_VECTOR ;i++){
    print_test("* Insertar Ultimo",lista_insertar_ultimo(lista,&vector[i]));
  }
  int contador = 0;
  lista_iterar(lista,sumar_primeros_cinco,&contador);
  print_test("* Sumar los primero 5 elemento es 15", contador == 15 );
  lista_destruir(lista,NULL);
}

void borrar_ordenado (lista_t *lista){
  lista_iter_t *iter = lista_iter_crear(lista);
  print_test("* Nuevo iterador esta al principio",lista_iter_ver_actual(iter) == lista_ver_primero(lista));
  for(int i=0 ; i < (TAM_INSERTAR_ITERADOR/2) ; i++)
    print_test("* Borrar primero",lista_iter_borrar(iter));
  printf("* Nuevo primero es: %i\n",*(int*)lista_ver_primero(lista) );
  lista_iter_destruir(iter);
  return;
}
void borrar_desordenado(lista_t *lista){
  lista_iter_t *iter = lista_iter_crear(lista);
  while(!lista_iter_al_final(iter)){
    printf(" [%i]",*(int*)lista_iter_ver_actual(iter));
    lista_iter_avanzar(iter);
  }
  lista_iter_destruir(iter);
  iter = lista_iter_crear(lista);
  print_test("\n* Nuevo iterador esta al principio",lista_iter_ver_actual(iter) == lista_ver_primero(lista));
  lista_iter_avanzar(iter);
  lista_iter_avanzar(iter);
  print_test("* Borrar poscion 3",lista_iter_borrar(iter));
  lista_iter_avanzar(iter);
  print_test("* Borrar poscion 5",lista_iter_borrar(iter));
  lista_iter_destruir(iter);
  iter = lista_iter_crear(lista);
  while(!lista_iter_al_final(iter)){
    printf(" [%i]",*(int*)lista_iter_ver_actual(iter));
    lista_iter_avanzar(iter);
  }
  lista_iter_destruir(iter);
  return;
}
void prueba_iter_externo_insertar_varios_elementos(){
  printf("\n++++++ Insertar Varios elemento ++++++\n" );
  int vector[TAM_INSERTAR_ITERADOR] = ELEMENTOS_A_INSERTAR;
  lista_t *lista = lista_crear();
  lista_iter_t *iter = lista_iter_crear(lista);
  print_test("* Insertar en lista vacia", lista_iter_insertar(iter,&vector[0]));
  printf("Actual es: %i\n",* (int*) lista_iter_ver_actual(iter) );
  for(int i=1 ; i < TAM_INSERTAR_ITERADOR ; i++){
    print_test("* Avanzar",lista_iter_avanzar(iter));
    print_test("* Insertar en lista", lista_iter_insertar(iter,&vector[i]));
  }
  printf("Actual es : %i \n", *(int*)(lista_iter_ver_actual(iter)));
  lista_iter_avanzar(iter);
  print_test("* Iter esta al final ",lista_iter_al_final(iter));
  printf("* Lista ver ultimo %i\n",*(int*)lista_ver_ultimo(lista));
  lista_iter_destruir(iter);
  borrar_ordenado(lista);
  borrar_desordenado(lista);
  lista_destruir(lista,NULL);
}

void prueba_iter_externo_recorrer_varios_elementos(void){
  printf("\n++++++ recorrer Varios elemento ++++++\n" );
  lista_t *lista = lista_crear();
  print_test("* Crear una lista",!(lista == NULL));
  int vector[20];
  printf("* Preparando la lista \n");
  for(int i=0; i < 20 ;i++){
    vector[i] = (i+1);
    lista_insertar_ultimo(lista,&vector[i]);
  }
  lista_iter_t *iter = lista_iter_crear(lista);
  print_test("* Iterador apuntando a primer elemento",lista_ver_primero(lista) == lista_iter_ver_actual(iter));
  print_test("* Iterador no esta al final",!lista_iter_al_final(iter));
  for(int i=1; i < 20 ;i++){// Avanza hasta 1 elemento mas de los enlistados
    print_test("* Iterador avanzar",lista_iter_avanzar(iter));
    print_test("* Iterador es el elemento esperado",lista_iter_ver_actual(iter) == &vector[i]);
  }
  lista_iter_avanzar(iter);
  print_test("* Iterador esta al final",lista_iter_al_final(iter));
  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  printf("\n++++++ Fin recorrer varios elemento ++++++\n" );

}

void prueba_iter_externos_1_elemento(void){
  printf("\n++++++ 1 elemento ++++++\n" );
  lista_t *lista = lista_crear();
  print_test("* Crear una lista",!(lista == NULL));
  lista_iter_t *iter = lista_iter_crear(lista);
  int *numero = malloc(sizeof(int));
  print_test("* Alloc del elemento",numero != NULL);
  *numero = 10;
  printf("El dato a insertar es [%i]\n",*numero);
  print_test("* Insertar con interador",lista_iter_insertar(iter,numero));
  print_test("* Ver primero y iter ver actual",((lista_ver_primero(lista)) && (lista_iter_ver_actual(iter)) ));
  print_test("* Eliminar elemento",lista_iter_borrar(iter));
  print_test("* Lista esta vacia",lista_esta_vacia (lista));
  print_test("* Lista iter esta al final",lista_iter_ver_actual(iter)==NULL);
  print_test("* Insertar al final con lista vacia e iter en NULL",lista_iter_insertar(iter,numero));
  printf("El ultimo es [%i] \n",*(int*)lista_ver_ultimo(lista));
  print_test("* Iter NO esta al final",!lista_iter_al_final(iter));
  print_test("* Eliminar elemento",lista_iter_borrar(iter) == numero);
  print_test("* El largo es 0",lista_largo(lista)==0);
  lista_iter_destruir(iter);
  lista_insertar_ultimo(lista,numero);
  print_test("Insertar ultimo en lista vacia es primero",lista_ver_primero(lista)== lista_ver_ultimo(lista));
  lista_destruir(lista,free);
  printf("\n++++++ Fin 1 elemento ++++++\n" );
}

void prueba_iter_externos(void){
  printf("\n++++++ Pruebas de las PRIMITIVAS de la iterador externo ++++++\n" );
  prueba_iter_externos_1_elemento();
  prueba_iter_externo_recorrer_varios_elementos();
  prueba_iter_externo_insertar_varios_elementos();
  iter_ext_insertar_desordenado();
}

void primitivas_lista(void){
  printf("++++++ Pruebas de las PRIMITIVAS de la lista ++++++\n" );
  lista_t *lista = lista_crear();
  int numero = 1;
  char vector[TAM_VECTOR] = {'a','b','c','d','e','f','g','h','i','j'};
  print_test("* Crear una lista",!(lista == NULL));
  print_test("* Lista esta vacia",lista_esta_vacia(lista));
  print_test("* Insertar primero",lista_insertar_primero(lista,&numero));
  print_test("* Lista ver primero", (&numero == lista_ver_primero (lista) ) );
  print_test("* Ver primero = Ver ultimo",lista_ver_primero(lista) == lista_ver_ultimo(lista));
  print_test("* Largo de la lista es 1", lista_largo(lista) == 1 );
  printf("++++++ Pruebas en volumen \n");
  printf("* El ultimo elemento a insertar es -> '%c'\n",vector[9] );
  for(int i = 0; i < TAM_VECTOR ;i++){
    print_test("** Insertar ultimo",lista_insertar_ultimo(lista,&vector[i]));
  }
  print_test("* Lista ver primero", (&numero == lista_ver_primero (lista) ) );
  printf("* El ultimo elemento es -> '%c'\n",*((char*)lista_ver_ultimo(lista)));
  print_test("** Borrar primero",lista_borrar_primero(lista) == &numero);
  for(int i = 0;i < TAM_VECTOR;i++){
    print_test("** Borrar primero",*((char*)lista_borrar_primero(lista)) == vector [i]) ;
  }
  print_test("* Lista esta vacia",lista_esta_vacia(lista));
  lista_destruir(lista,NULL);

}

void pruebas_lista_alumno(void){
  primitivas_lista();
  prueba_iter_externos();
  prueba_iter_internos();
  printf("\n Total de errores %i\n",failure_count() );
  return;
}
