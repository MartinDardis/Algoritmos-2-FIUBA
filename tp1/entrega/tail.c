/*DEPENDE DE COLA.H  */
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

#define ARG_ESPERADOS 2
#define ERROR_CANT_ARG 0
#define ARG_NO_ES_NUMERO 0


void imprimir_lineas(void* linea);
void leer_lineas(cola_t* cola_lineas,size_t cant_a_leer);

int main (int argc,char* argv[]){
  if (argc != ARG_ESPERADOS){
    fprintf(stderr,"Cantidad de parametros erronea");
    return ERROR_CANT_ARG;
  }
  size_t cant_a_leer = (size_t) atoi(argv[1]);
  if( cant_a_leer == 0 ){
    fprintf(stderr,"Tipo de parametro incorrecto");
    return ARG_NO_ES_NUMERO;
  }
  cola_t* lineas_a_imprimir = cola_crear();
  leer_lineas(lineas_a_imprimir,cant_a_leer);
  cola_destruir(lineas_a_imprimir,imprimir_lineas);
  return 0;
}

void leer_lineas(cola_t* cola_lineas,size_t cant_a_leer){
  size_t cant_leidas = 0;
  char* buffer = NULL;
  size_t cantidad = 0;
  ssize_t leidos = 0;
  while( (leidos = getline(&buffer,&cantidad,stdin)) > 0 ){
    if(cant_leidas < cant_a_leer){
        cola_encolar(cola_lineas,buffer);//Encolo la linea obtenida
    }
    else{
      free(cola_desencolar(cola_lineas));//libero la linea encolada primero
      cola_encolar(cola_lineas,buffer);//Encolo la linea leida
    }
    cant_leidas++;
    cantidad = 0;//Limpio buffer
    buffer = NULL;//Limpio buffer
  }
  free(buffer);//Libero Buffer
  return;
}

void imprimir_lineas(void* linea){
  printf("%s",(char*)linea);
  free(linea);
  return;
}
