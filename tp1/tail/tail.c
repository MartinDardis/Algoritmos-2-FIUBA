/*DEPENDE DE COLA.H  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cola.h"

#define _POSIX_C_SOURCE 200809L
#define ARG_ESPERADOS 2
#define ERROR_CANT_ARG -1
#define ARG_NO_ES_NUMERO -2


void imprimir_lineas(void* linea);
void leer_lineas(cola_t* cola_lineas,size_t cant_a_leer);

int main (int argc,char* argv[]){
  if (argc != ARG_ESPERADOS){
    perror("Cantidad de parametros erronea");
    return ERROR_CANT_ARG;
  }
  size_t cant_a_leer = atoi(argv[1]);
  if( cant_a_leer == 0 ){
    perror("Tipo de parametro incorrecto");
    return ARG_NO_ES_NUMERO;
  }
  cola_t* lineas_a_imprimir = cola_crear();
  leer_lineas(lineas_a_imprimir,cant_a_leer);
  imprimir_lineas(lineas_a_imprimir);
  cola_destruir(lineas_a_imprimir,imprimir_lineas);
  return 0;
}

void leer_lineas(cola_t* cola_lineas,size_t cant_a_leer){
  size_t cant_leidas=0;
  char* buffer;
  size_t cantidad = 0;
  while( !feof(stdin) ){
    getline(&buffer,&cantidad,stdin);
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

void imprimir_lineas(void* linea){
  printf("%s\n",(char*)linea);
  free(linea);
  return;
}
