#include <string.h>
#include "heap.h"
#include "testing.h"

void crear_y_destruir();
int to_strcmp(const void* a,const void* b){
  return strcmp((char*)a,(char*)b);
}
void pruebas_heap_alumno(void){
  crear_y_destruir();
}


void crear_y_destruir(){
  heap_t* heap = heap_crear(to_strcmp);
  print_test("* Crear un heap",heap != NULL);
  heap_destruir(heap,NULL);
}
