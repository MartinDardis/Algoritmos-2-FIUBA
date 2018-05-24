#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define APOSTROFE '\''
#define CORCHETE_ABIERTO '['
#define CORCHETE_CERRADO ']'
#define PARENTESIS_ABIERTO '('
#define PARENTESIS_CERRADO ')'
#define LLAVE_ABIERTA '{'
#define LLAVE_CERRADA '}'

int main(int argc,char* argv[]){
    char* buffer = NULL;
    size_t cantidad = 0;
    ssize_t leidos = 0;
    while( (leidos = getline(&buffer,&cantidad,stdin)) > 0){
      bool balanceado = comprobar_linea(buffer);
      imprimir_resultado(balanceado);
      free(buffer);
      cantidad = 0;//Limpio buffer
      buffer = NULL;//Limpio buffer
    }
    free(buffer);
    return 0;
}
