#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void liberar_por_error(char* vector_str[],size_t pos){
  for(size_t i=0;i<pos;i++)
    free(vector_str[i]);
  return;
}
size_t recorrer_cadena_split(const char* str, size_t* cant_de_sep, char sep){
  size_t i = 0;
  while( str[i] != '\0'){
    if ( str[i] == sep)
      (*cant_de_sep)++;
    i++;
  }
  return i;
}
char** split(const char* str, char sep){
  size_t cant_de_cadenas = 1;
  size_t cant_carcteres = recorrer_cadena_split(str,&cant_de_cadenas,sep);
  if (sep == '\0' )
    return NULL;
  char** vector_str = malloc( (cant_de_cadenas) * sizeof(char*) );
  if ( vector_str == NULL)
    return NULL;
  size_t pos=0,j=0;
  for (size_t i=0; i <= cant_carcteres ; i++){
    if(str[i] == sep || i == cant_carcteres ){
      vector_str[pos] = malloc ((i-j) * sizeof(char));
      if (vector_str[pos] == NULL){
        liberar_por_error(vector_str,pos);
        return NULL
      }
      strncpy(vector_str[pos],&str[j],(i-j));
      j = i+1;
      pos++;
    }
  }
  (vector_str[pos]) = NULL;
  return vector_str;
}

size_t tam_string_join(char* strv[]){
  size_t largo = 0;
  size_t pos = 0;
  while (strv[pos] != NULL) {
    largo += strlen(strv[pos]);
    pos++;
  }
  return largo;
}
char* join(char** strv, char sep){
  if(strv == NULL)
    return NULL;
  char* string = malloc(tam_string_join(strv) * sizeof(char*));
  size_t pos = 0;
  while (strv[pos] != NULL){
    strcat(string,strv[pos]);
    if(strv[pos+1]!= NULL)
      strncat(string,&sep,sizeof(sep));
    pos++;
  }
  return string;
}

void free_strv(char* strv[]){
  size_t i = 0;
  while(strv[i] == NULL){
    free (strv[i]);
    i++;
  }
  free(strv);
  return;
}
