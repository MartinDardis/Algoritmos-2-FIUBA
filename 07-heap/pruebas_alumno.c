#include <string.h>
#include "heap.h"
#include "testing.h"

void pruebas_crear_y_destruir();
void pruebas_encolar_y_desencolar();
int to_strcmp(const void* a,const void* b){
    return strcmp((char*)a,(char*)b);
}

void pruebas_heap_alumno(void){
    pruebas_crear_y_destruir();
    pruebas_encolar_y_desencolar();
}


void pruebas_crear_y_destruir(){
    heap_t* heap = heap_crear(to_strcmp);
    print_test("* Crear un heap",heap != NULL);
    print_test("Heap nuevo tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);

    char* arr [7]= {"a","g","c","b","d","f","e"};
    heap = heap_crear_arr((void**)arr, 7, to_strcmp);
    print_test("Heap nuevo creado con array tiene cantidad = 7", heap_cantidad(heap) == 7);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        heap_desencolar(heap);
        //print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr[i]);
        //print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr[i]);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
}

void pruebas_encolar_y_desencolar(){
    heap_t* heap = heap_crear(to_strcmp);
    print_test("* Crear un heap",heap != NULL);
    print_test("Heap nuevo tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));
    char* arr1 [7]= {"h","n","j","i","k","m","l"};
    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1[i]);
    }
    print_test("Heap nuevo creado con array tiene cantidad = 7", heap_cantidad(heap) == 7);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        heap_desencolar(heap);
        //print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1[i]);
        //print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1[i]);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);

    char* arr2 [7]= {"a","g","c","b","d","f","e"};
    heap = heap_crear_arr((void**)arr2, 7, to_strcmp);
    print_test("Heap nuevo creado con array tiene cantidad = 7", heap_cantidad(heap) == 7);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1[i]);
    }
    print_test("Heap nuevo creado con array tiene cantidad = 14", heap_cantidad(heap) == 14);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        heap_desencolar(heap);
        //print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1[i]);
        //print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1[i]);
    }
    for(int i=0;i<7;i++){
        heap_desencolar(heap);
        //print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr2[i]);
        //print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr2[i]);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
}
