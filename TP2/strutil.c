#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* strndup (const char *s, size_t n){
  char *result;
  size_t len = strlen(s);
  if (n < len)
    len = n;
  result = (char *) malloc (len + 1);
  if (!result)
    return 0;
  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
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
  size_t cant_carcteres =+ recorrer_cadena_split(str,&cant_de_cadenas,sep);
  if (sep == '\0' )
    return NULL;
  char** vector_str = malloc( (cant_de_cadenas+1) * sizeof(char*) );
  if ( vector_str == NULL)
    return NULL;
  size_t pos=0,j=0;
  for (size_t i=0; i <= cant_carcteres ; i++){
    if(str[i] == sep || i == cant_carcteres ){
      vector_str[pos] = strndup(&str[j],(i-j));
      if(vector_str[pos] == NULL ){
        liberar_por_error(vector_str,pos);
        return NULL;
      }
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
    largo += strlen(strv[pos])+1;//+1 por el separador
    pos++;
  }
  return largo+1;
}
char* join(char** strv, char sep){
  if(strv == NULL)
    return NULL;
  size_t tam = tam_string_join(strv);
  char* string = malloc(tam * sizeof(char*));
  if (string == NULL)
    return NULL;
  size_t pos = 0 , largo = 0;
  while(strv[pos] != NULL){
    size_t i = 0;
    while(strv[pos][i] != '\0'){
      string[largo] = strv[pos][i];
      i++;
      largo++;
    }
    pos++;
    if(strv[pos] != NULL){
      string[largo] = sep;
      largo++;
    }
  }
  string[largo] = '\0';
  return string;
}

void free_strv(char* strv[]){
  size_t i = 0;
  while(strv[i] != NULL){
    free (strv[i]);
    i++;
  }
  free(strv[i]);
  free(strv);
  return;
}
