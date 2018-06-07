#include <string.h>
#include "heap.h"
#include "testing.h"

void pruebas_crear_y_destruir_int();
void pruebas_encolar_y_desencolar_int();
void pruebas_heapsort_int();
void pruebas_crear_y_destruir_str();
void pruebas_encolar_y_desencolar_str();
void pruebas_heapsort_str();

void pruebas_heap_alumno(void){
    /*
    pruebas_crear_y_destruir_int();
    pruebas_encolar_y_desencolar_int();
    pruebas_heapsort_int();
    */
    pruebas_crear_y_destruir_str();
    pruebas_encolar_y_desencolar_str();
    pruebas_heapsort_str();
}

int int_cmp(const void* a,const void* b){
    if(*(int*)a < *(int*)b){
        return -1;
    }
    if(*(int*)a > *(int*)b){
        return 1;
    }
    return 0;
}

int to_strcmp(const void* a,const void* b){
    return strcmp((char*)a,(char*)b);
}






/*
void pruebas_crear_y_destruir_int(){
    heap_t* heap = heap_crear(int_cmp);
    print_test("* Crear un heap",heap != NULL);
    print_test("Heap nuevo tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);

    int arr [7]= {1, 7, 3, 2, 4, 6, 5};
    heap = heap_crear_arr((void**)arr, 7, int_cmp);
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

void pruebas_encolar_y_desencolar_int(){
    heap_t* heap = heap_crear(int_cmp);

    size_t cantidad = 0;
    print_test("* Crear un heap",heap != NULL);
    print_test("Heap nuevo tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));
    int arr1a [7]= {8, 14, 10, 9, 11, 12, 13};
    int arr1b [7]= {14, 13, 12, 11, 10, 9, 8};
    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1a[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == ++cantidad);
    }
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr1b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);

    cantidad = 0;
    int arr2a [7]= {1, 7, 3, 2, 4, 6, 5};
    int arr2b [7]= {7, 6, 5, 4, 3, 2, 1};
    heap = heap_crear_arr((void**)arr2a, 7, int_cmp);
    print_test("Heap nuevo creado con array tiene cantidad = 7", heap_cantidad(heap) == 7);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1a[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == ++cantidad);
    }
    print_test("Heap nuevo creado con array tiene cantidad = 14", heap_cantidad(heap) == 14);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr1b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr2b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr2b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr2b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
}

void pruebas_heapsort_int(){
    int arr1a [7]= {1, 7, 3, 2, 4, 6, 5};
    int arr1b [7]= {7, 6, 5, 4, 3, 2, 1};

    heap_sort((void**)arr1a, 7, int_cmp);

    for (int i = 0; i < 7; i++){
        print_test("Heapsort ordeno correctamente", int_cmp(arr1a[i], arr1b[i]) == 0);
    }

    bool ok = true;
    for (int i = 0; i < 7; i++){
        ok &= (int_cmp(arr1a[i], arr1b[i]) == 0);
    }
    print_test("Heapsort ordeno correctamente", ok);

}
*/











void pruebas_crear_y_destruir_str(){
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

void pruebas_encolar_y_desencolar_str(){
    heap_t* heap = heap_crear(to_strcmp);

    size_t cantidad = 0;
    print_test("* Crear un heap",heap != NULL);
    print_test("Heap nuevo tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));
    char* arr1a [7]= {"h","n","j","i","k","m","l"};
    char* arr1b [7]= {"n","m","l","k","j","i","h"};
    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1a[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == ++cantidad);
    }
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr1b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);

    cantidad = 7;
    char* arr2a [7]= {"a","g","c","b","d","f","e"};
    char* arr2b [7]= {"g","f","e","d","c","b","a"};
    heap = heap_crear_arr((void**)arr2a, 7, to_strcmp);
    print_test("Heap nuevo creado con array tiene cantidad = 7", heap_cantidad(heap) == 7);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i = 0; i < 7; i++){
        heap_encolar(heap, arr1a[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == ++cantidad);
    }
    print_test("Heap nuevo creado con array tiene cantidad = 14", heap_cantidad(heap) == 14);
    print_test("Heap nuevo creado con array no esta vacio", !heap_esta_vacio(heap));

    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr1b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr1b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr1b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    for(int i=0;i<7;i++){
        print_test("Heap ver max tiene valor correcto", heap_ver_max(heap) == arr2b[i]);
        print_test("Heap desencolar tiene valor correcto", heap_desencolar(heap) == arr2b[i]);
        print_test("Heap ver max cambio de valor", heap_ver_max(heap) != arr2b[i]);
        print_test("Heap nuevo creado con array tiene cantidad correcta", heap_cantidad(heap) == --cantidad);
    }
    print_test("Heap tiene cantidad = 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
}

void pruebas_heapsort_str(){
    char* arr1a [7]= {"a","g","c","b","d","f","e"};
    char* arr1b [7]= {"a","b","c","d","e","f","g"};

    heap_sort((void**)arr1a, 7, to_strcmp);

    for (int i = 0; i < 7; i++){
        print_test("Heapsort ordeno correctamente", strcmp(arr1a[i], arr1b[i]) == 0);
    }
    /*
    bool ok = true;
    for (int i = 0; i < 7; i++){
        ok &= (to_strcmp(arr1a[i], arr1b[i]) == 0);
    }
    print_test("Heapsort ordeno correctamente", ok);
    */
}
