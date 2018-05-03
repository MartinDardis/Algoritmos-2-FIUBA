#include <stdio.h>
#include "strutil.h"
#include <string.h>

int main (){
  char* frase = "Hola,todo,bien?,como,estas?";
  char* *frase_dividida = split(frase,',');
  int pos = 0;
  while ( frase_dividida[pos] != NULL){
    printf("[%s] ",frase_dividida[pos]);
    pos++;
  }
  printf("\n");
  char* frase_join = join(frase_dividida,';');
  printf("%s\n",frase_join);
  free_strv(frase_dividida);
 return 0;
}
