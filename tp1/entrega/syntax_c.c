#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pila.h"

#define APOSTROFE '\''
#define CORCHETE_ABIERTO '['
#define CORCHETE_CERRADO ']'
#define PARENTESIS_ABIERTO '('
#define PARENTESIS_CERRADO ')'
#define LLAVE_ABIERTA '{'
#define LLAVE_CERRADA '}'

void imprimir_resultado(bool estado);
bool comprobar_linea(char* linea);
bool comparar_par(char abierto,char cerrado);

int main(int argc,char* argv[]){
    char* buffer = NULL;
    size_t cantidad = 0;
    ssize_t leidos = 0;
    while ( (leidos = getline(&buffer,&cantidad,stdin)) > 0){
      bool resultado = comprobar_linea(buffer);
      imprimir_resultado(resultado);
      free(buffer);
      cantidad = 0;//Limpio buffer
      buffer = NULL;//Limpio buffer
    }
    free(buffer);
    return 0;
}

bool comprobar_linea(char* linea){
  if (strlen (linea) == 0)
    return true;
  pila_t* abiertos = pila_crear();
  if (!abiertos)
    return false;
  bool balanceado = true;
  for(size_t i=0; linea[i]!= '\0' && balanceado; i++){
    if (linea[i] == LLAVE_ABIERTA || linea[i] == CORCHETE_ABIERTO || linea[i] == PARENTESIS_ABIERTO){
      char* apilar = malloc(sizeof(char));
      if(!apilar)
        return false; // Error de apilado
      apilar[0] = linea[i];
      pila_apilar(abiertos,apilar);
    }
    if (linea[i] == LLAVE_CERRADA || linea[i]==CORCHETE_CERRADO || linea[i] == PARENTESIS_CERRADO){
      if (pila_esta_vacia(abiertos))
        balanceado = false;
      else {
        char* abierto = (char*) pila_desapilar(abiertos);
        balanceado = comparar_par(abierto[0],linea[i]);
        free(abierto);
      }
    }
    if (linea[i] == APOSTROFE){
      i++;
      while (linea[i] != APOSTROFE && linea[i] != '\0') {
        i++;
        if(linea[i] == '\0')
          balanceado = false;
      }
    }

  }
  if(!pila_esta_vacia(abiertos)){
    balanceado = false;
    while(!pila_esta_vacia(abiertos))
      free(pila_desapilar(abiertos));
  }
  pila_destruir(abiertos);
  return balanceado;
}

bool comparar_par(char abierto,char cerrado){
  bool coincide = false;
  switch (abierto) {
    case PARENTESIS_ABIERTO:
      if (cerrado == PARENTESIS_CERRADO)
        coincide = true;
      break;
    case LLAVE_ABIERTA:
      if ( cerrado == LLAVE_CERRADA)
        coincide = true;
      break;
    case CORCHETE_ABIERTO:
      if ( cerrado == CORCHETE_CERRADO)
        coincide = true;
      break;
  }
  return coincide;
}

void imprimir_resultado (bool estado){
  if(estado)
    printf("OK\n");
  else
    printf("ERROR\n");
  return;
}
