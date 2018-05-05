
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
  FILE* archivo_1 = fopen ("nombres_1.txt","wt");
  fprintf(archivo_1, "%s\n%s\n%s\n%s\n","Alicia","Bruno","Carolina","Daniel");
  fclose(archivo_1);

  FILE* archivo_2 = fopen ("nombres_2.txt","wt");
  fprintf(archivo_2, "%s\n%s\n%s\n%s\n","Alicia","Bruno","Roberto","Daniel");
  fclose(archivo_2);

  FILE* archivo_3 = fopen ("nombres_3.txt","wt");
  fprintf(archivo_2, "%s\n%s\n%s\n","Alicia","Carolina","Alberto");
  fclose(archivo_2);

  return 0;
}
