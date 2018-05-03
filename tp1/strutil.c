#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char** split(const char* str, char sep){
  if (sep == '\0')
    return NULL;
  size_t cant_carcteres = strlen(str);
  char** vector_str = malloc( (cant_carcteres) * sizeof(char*) ); // Suponiendo que todos los caracteres de la cadena se encuentre separador por SEP
  if ( vector_str == NULL )
    return NULL;
  size_t pos=0,j=0;
  for (size_t i=0; i <= cant_carcteres ; i++){
    if(str[i] == sep || i == cant_carcteres ){
      vector_str[pos] = malloc ((i-j) * sizeof(char));
      strncpy(vector_str[pos],&str[j],(i-j));
      j = i+1;
      pos++;
    }
  }
  (vector_str[pos]) = NULL;
  return vector_str;
}

char* join(char** strv, char sep){
  char* string = malloc(1000 * sizeof(char*));
  size_t pos = 0;
  while (strv[pos] != NULL){
    strcat(string,strv[pos]);
    if(strv[pos+1]!= NULL)
      strncat(string,&sep,1);
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
