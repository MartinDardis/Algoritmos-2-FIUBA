/*DEPENDE DE COLA.H  */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cola.h"

#define ERROR_CANT_ARG -1
#define ARG_NO_ES_NUMERO 1
#define TAM_BUFFER 150

int main (int argc,char* argv){
  if (argc != 2){
    printf("Cantidad de argumentos erronea\n");
    return ERROR_CANT_ARG;
  }
  size_t cant_a_leer = atoi(argv[1]);
  if( cant_de_lineas == 0 )
    return ARG_NO_ES_NUMERO;
  cola_t* cola_lineas = cola_crear();
  size_t cant_leidas;
  char* buffer = malloc(TAM_BUFFER * sizeof(char*));
  while( fread(stdin,"%s",&buffer) ){
    if(cant_leidas <= cant_a_leer+1){
      cola_encolar(cola_lineas,&buffer);
      buffer = malloc(TAM_BUFFER * sizeof(char*));
    }
    else{
      free(cola_desencolar(cola_lineas));
      cola_encolar(cola_lineas,&buffer);
      buffer = malloc(TAM_BUFFER * sizeof(char*));
    }
  }

  return 0;
}
