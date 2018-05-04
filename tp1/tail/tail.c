/*DEPENDE DE COLA.H  */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cola.h"

#define _POSIX_C_SOURCE 200809L
#define ERROR_CANT_ARG -1
#define ARG_NO_ES_NUMERO 1

void imprimir_lineas(void* linea){
  printf("%s\n",(char*)linea);
  free(linea);
  return;
}


void leer_lineas(cola_t* cola_lineas,size_t cant_a_leer){
  size_t cant_leidas=0;
  char* buffer;
  size_t cantidad = 0;
  while( !feof(stdin) ){
    getline(&buffer,&cantidad,stdin)
    if(cant_leidas <= cant_a_leer){
        cola_encolar(cola_lineas,&buffer);
    }
    else{
      free(cola_desencolar(cola_lineas));
      cola_encolar(cola_lineas,&buffer);
    }
    cant_leidas++;
    buffer = NULL;
  }
  return;
}


int main (int argc,char* argv[]){
  if (argc != 2){
    printf("Cantidad de argumentos erronea\n");
    return ERROR_CANT_ARG;
  }
  size_t cant_a_leer = 100 ;//atoi(argv[1]);
  if( cant_a_leer == 0 ){
    printf("Argumento erroneo\n");
    return ARG_NO_ES_NUMERO;
  }
  cola_t* lineas_a_imprimir = cola_crear();
  leer_lineas(lineas_a_imprimir,cant_a_leer);
  imprimir_lineas(lineas_a_imprimir);
  cola_destruir(lineas_a_imprimir,imprimir_lineas);
  return 0;
}
