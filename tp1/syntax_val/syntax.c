#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _POSIX_C_SOURCE 200809L
#define APOSTROFE '\''
#define CORCHETE_ABIERTO '['
#define CORCHETE_CERRADO ']'
#define PARENTESIS_ABIERTO '('
#define PARENTESIS_CERRADO ')'
#define LLAVE_ABIERTA '{'
#define LLAVE_CERRADA '}'

bool comprobar_linea(char* buffer);
void imprimir_resultado(bool estado);
bool comprobar_apostrofe(char* linea,size_t* i);
bool comprobar_corchetes(char* linea, size_t* i);
bool comprobar_parentesis(char* linea,size_t* i);
bool comprobar_llaves(char* linea,size_t* i);

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

bool comprobar_linea(char* linea){
  for( size_t i = 0 ; linea[i] != '\0';i++){
    if (linea[i] == APOSTROFE ){
      if(!comprobar_apostrofe(linea,&i))
        return false;
    }
    if (linea[i] == CORCHETE_ABIERTO){
      if(!comprobar_corchetes(linea,&i))
        return false;
    }
    if (linea[i] == PARENTESIS_ABIERTO){
      if(!comprobar_parentesis(linea,&i))
        return false;
    }
    if (linea[i] == LLAVE_ABIERTA){
    if(!comprobar_llaves(linea,&i))
      return false;
    }
  }
  return true;
}

bool comprobar_apostrofe(char* linea,size_t* i){
  (*i)++;
  while (linea[*i] != APOSTROFE){
    if (linea[*i] == '\0')
      return false;
    (*i)++;
  }
  return true;
}

bool comprobar_corchetes(char* linea, size_t* i){
  (*i)++;
  while (linea[*i] != CORCHETE_CERRADO){
    if (linea[*i] == '\0')
      return false;
    if(linea[*i] == APOSTROFE){
      if(!comprobar_apostrofe(linea,i))
        return false;
    }
    if(linea[*i] == PARENTESIS_ABIERTO){
      if(!comprobar_parentesis(linea,i))
        return false;
    }
    if(linea[*i] == LLAVE_ABIERTA){
      if(!comprobar_llaves(linea,i))
        return false;
    }
    (*i)++;
  }
  return true;
}

bool comprobar_parentesis(char* linea,size_t* i){
  (*i)++;
  while (linea[*i] != PARENTESIS_CERRADO){
    if (linea[*i] == '\0')
      return false;
    if(linea[*i] == APOSTROFE){
      if(!comprobar_apostrofe(linea,i))
        return false;
    }
    if(linea[*i] == CORCHETE_ABIERTO){
      if(!comprobar_corchetes(linea,i))
        return false;
    }
    if(linea[*i] == LLAVE_ABIERTA){
      if(!comprobar_llaves(linea,i))
        return false;
    }
    (*i)++;
  }
  return true;
}

bool comprobar_llaves(char* linea,size_t* i){
  (*i)++;
  while (linea[*i] != LLAVE_CERRADA){
    if (linea[*i] == '\0')
      return false;
    if(linea[*i] == APOSTROFE){
      if(!comprobar_apostrofe(linea,i))
        return false;
    }
    if(linea[*i] == CORCHETE_ABIERTO){
      if(!comprobar_corchetes(linea,i))
        return false;
    }
    if(linea[*i] == PARENTESIS_ABIERTO){
      if(!comprobar_parentesis(linea,i))
        return false;
    }
    (*i)++;
  }
  return true;

}

void imprimir_resultado (bool estado){
  if(estado)
    printf("OK\n");
  else
    printf("ERROR\n");
  return;
}
