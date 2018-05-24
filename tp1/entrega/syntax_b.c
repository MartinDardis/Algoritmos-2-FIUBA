#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"

#define APOSTROFE '\''
#define CORCHETE_ABIERTO '['
#define CORCHETE_CERRADO ']'
#define PARENTESIS_ABIERTO '('
#define PARENTESIS_CERRADO ')'
#define LLAVE_ABIERTA '{'
#define LLAVE_CERRADA '}'

bool comprobar_linea (char* linea);
lista_t* buscar_caracteres (char* linea);
bool comprobar_balance (lista_t* caracteres);
bool enlistar_caracter (char caracter, lista_t* lista);
void* eliminar_por_error (lista_t* lista);
void imprimir_resultado(bool estado);
void eliminar_par(lista_t* lista);

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

bool comprobar_linea (char* linea){
  lista_t* caracteres = buscar_caracteres(linea);
  if (!caracteres)
    return false;
  bool balanceado = comprobar_balance(caracteres);
  lista_destruir(caracteres,free);
  return balanceado;
}

lista_t* buscar_caracteres (char* linea){
  if(strlen(linea) == 0)
    return NULL;
  lista_t* lista = lista_crear();
  for(size_t i=0; linea[i] != '\0' ; i++){
    if(linea[i] == CORCHETE_ABIERTO || linea[i] == CORCHETE_CERRADO){
      if (!enlistar_caracter(linea[i],lista)){
        return eliminar_por_error(lista);
      }
    }
    else if (linea[i] == LLAVE_ABIERTA || linea[i] == LLAVE_CERRADA){
      if (!enlistar_caracter(linea[i],lista)){
        return eliminar_por_error(lista);
      }
    }
    else if (linea[i] == PARENTESIS_ABIERTO || linea[i] == PARENTESIS_CERRADO){
      if (!enlistar_caracter(linea[i],lista)){
        return eliminar_por_error(lista);
      }
    }
    else if (linea[i] == APOSTROFE){
        while (linea[i] != APOSTROFE && linea[i] != '\0'){
          i++;
        }
        i++;
      }
  }
  return lista;
}

void* eliminar_por_error (lista_t* lista){
  lista_destruir(lista,free);
  return NULL;
}

bool enlistar_caracter (char caracter,lista_t* lista){
  char* insertar = malloc( sizeof(char) );
  if(!insertar)
    return false;
  insertar[0] = caracter;
  lista_insertar_ultimo(lista,insertar);
  return true;
}

bool comprobar_balance (lista_t* caracteres){
  bool balanceado = true;
  while ( !lista_esta_vacia (caracteres) && balanceado == true ){
    char primero =  *((char*) lista_ver_primero(caracteres));
    char ultimo =  *((char*) lista_ver_ultimo(caracteres));
    if ( primero == CORCHETE_ABIERTO){
      if ( ultimo == CORCHETE_CERRADO)
        eliminar_par(caracteres);
      else balanceado = false;
    }
    else if ( primero == LLAVE_ABIERTA){
      if ( ultimo == LLAVE_CERRADA)
        eliminar_par(caracteres);
      else balanceado = false;
    }
    else if ( primero == PARENTESIS_ABIERTO){
      if ( ultimo == PARENTESIS_CERRADO)
        eliminar_par(caracteres);
      else balanceado = false;
    }
    else
      balanceado = false;
  }
  if (!lista_esta_vacia(caracteres))
    return false;
  return balanceado;
}

void eliminar_par(lista_t* caracteres){
  lista_iter_t* iter = lista_iter_crear(caracteres);
  size_t largo = lista_largo(caracteres);
  for (size_t i=1; i < largo ;i++)
    lista_iter_avanzar(iter);
  free(lista_iter_borrar(iter));
  lista_iter_destruir(iter);
  free(lista_borrar_primero(caracteres));
  return;
}


void imprimir_resultado (bool estado){
  if(estado)
    printf("OK\n");
  else
    printf("ERROR\n");
  return;
}
