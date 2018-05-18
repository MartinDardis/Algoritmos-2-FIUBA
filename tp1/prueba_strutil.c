#include <stdio.h>
#include <stdlib.h>
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
  free(frase_join);

  frase =",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";
  char** spl_1 = split(frase,',');
  pos = 0;
  while ( spl_1[pos] != NULL){
    printf("[%s] ",spl_1[pos]);
    pos++;
  }
  printf("\n");
  char* spl_join_1 = join(spl_1,';');
  printf("%s\n",spl_join_1);
  free(spl_join_1);
  free_strv(spl_1);

  frase ="hola,,todo,mal,,esto,,,anda,,mal";
  char** spl = split(frase,',');
  pos = 0;
  while ( spl[pos] != NULL){
    printf("[%s] ",spl[pos]);
    pos++;
  }
  printf("\n");
  char* spl_join = join(spl,';');
  printf("%s\n",spl_join);
  free(spl_join);
  free_strv(spl);
 return 0;
}
