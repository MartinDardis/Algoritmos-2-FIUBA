#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ARG_ESPERADOS 3
#define ERROR_CANT_ARG -1
#define ARCHIVO_ERRONEO -2

void comparar_archivos(FILE* archivo_1,FILE* archivo_2);
char* leer_linea(FILE* archivo);

int main(int argc,char* argv[]){
  if (argc != ARG_ESPERADOS){
    fprintf(stderr,"Cantidad de parametros erronea");
    return ERROR_CANT_ARG;
  }
  FILE* archivo_1 = fopen(argv[1],"r");
  if (!archivo_1){
    fprintf(stderr,"Archivo erroneo");
    return ARCHIVO_ERRONEO;
  }
  FILE* archivo_2 = fopen(argv[2],"r");
  if (!archivo_2){
    fprintf(stderr,"Archivo erroneo");
    return ARCHIVO_ERRONEO;
  }
  comparar_archivos(archivo_1,archivo_2);
  fclose(archivo_1);
  fclose(archivo_2);

  return 0;
}

void comparar_archivos(FILE* archivo_1, FILE* archivo_2){
  int linea = 1;
  char* linea_arch_1 = leer_linea(archivo_1);
  char* linea_arch_2 = leer_linea(archivo_2);
  while( !feof(archivo_1) && !feof(archivo_2) ){
    if (strcmp(linea_arch_1,linea_arch_2) != 0 ){
      fprintf(stdout,"Diferencia en linea %i\n< %s---\n> %s",linea,linea_arch_1,linea_arch_2);
    }
    linea++;
    free(linea_arch_1);
    free(linea_arch_2);
    linea_arch_1 = leer_linea(archivo_1);
    linea_arch_2 = leer_linea(archivo_2);
  }
  while ( !feof(archivo_1) ){
    fprintf(stdout,"Diferencia en linea %i\n< %s---\n> %s",linea,linea_arch_1,"");
    free(linea_arch_1);
    linea++;
    linea_arch_1 = leer_linea(archivo_1);
  }
  while ( !feof(archivo_2) ){
    fprintf(stdout,"Diferencia en linea %i\n< %s---\n> %s",linea,"",linea_arch_2);
    free(linea_arch_2);
    linea++;
    linea_arch_2 = leer_linea(archivo_2);
  }
  free(linea_arch_1);
  free(linea_arch_2);
  return;
}

char* leer_linea(FILE* archivo){
  char* buffer = NULL;
  size_t cant = 0;
  getline(&buffer,&cant,archivo);
  return buffer;
}
