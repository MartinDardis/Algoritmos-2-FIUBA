#include "heap.h"

#define TAM_INICIAL 10

struct heap{
    size_t cantidad;
    void** datos;
    size_t capacidad;
    cmp_func_t comparar;
};

/*                              Primitivas internas                           */
bool verificar_tam(heap_t* heap);
bool redimensionar(heap_t *heap, size_t tam);
void swap(void** a, void** b);
void upheap(void** arreglo, cmp_func_t cmp, size_t pos);
void downheap(void** arreglo, size_t cantidad, size_t pos_padre, cmp_func_t cmp);
void heapify(void** arreglo, size_t cantidad, cmp_func_t cmp);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void heap_sort(void** arreglo, size_t cantidad, cmp_func_t cmp){
    heapify(arreglo, cantidad, cmp);
    while(cantidad > 0){
        swap(&arreglo[0], &arreglo[cantidad-1]);
        cantidad--;
        downheap(arreglo, cantidad, 0, cmp);
    }
}

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap){
        return NULL;
    }

    heap->datos = malloc(TAM_INICIAL * sizeof(void*));
    if(! heap->datos){
        free (heap);
        return NULL;
    }

    heap->cantidad = 0;
    heap->capacidad = TAM_INICIAL;
    heap->comparar = cmp;
    return heap;
}

heap_t *heap_crear_arr(void** arreglo, size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap){
        return NULL;
    }

    void** datos = malloc(n * sizeof(void*));
    if(!datos){
        free(heap);
        return NULL;
    }

    for (size_t i = 0; i < n;i++){
        datos[i]=arreglo[i];
    }
    heapify(datos,n,cmp);

    heap->datos = datos;
    heap->cantidad = n;
    heap->capacidad = n;
    heap->comparar = cmp;
    return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if(destruir_elemento){
        for(int i=0; i< heap->cantidad;i++){
            destruir_elemento((heap->datos)[i]);
        }
    }

    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
    if (heap->cantidad == 0){
        return true;
    } else {
        return false;
    }
}

bool heap_encolar(heap_t *heap, void *elem){
    if (!heap) {
        return false;
    }
    if (!verificar_tam(heap)){
        return false;
    }

    size_t posc_nuevo = heap->cantidad;
    (heap->datos)[posc_nuevo] = elem;
    heap->cantidad++;
    upheap(heap->datos, heap->comparar, posc_nuevo);
    return true;
}

void* heap_ver_max(const heap_t* heap){
    if(heap->cantidad == 0){
        return NULL;
    }
    return (heap->datos)[0];
}

void *heap_desencolar(heap_t *heap){
    if(!heap){
        return NULL;
    }

    void* dato = (heap->datos)[0];
    size_t posc_ultimo = heap->cantidad-1;
    swap(&heap->datos[0], &heap->datos[posc_ultimo]);
    heap->cantidad--;

    downheap(heap->datos, heap->cantidad, 0, heap->comparar);
    verificar_tam(heap);
    return dato;
}

/* Funciones internas */

bool redimensionar(heap_t *heap, size_t tam){
    void* *datos_nuevos = realloc(heap->datos,tam * sizeof(void*));
    if (*datos_nuevos == NULL){
        return false;
    }
    heap->datos = datos_nuevos;
    heap->capacidad = tam;
    return true;
}

bool verificar_tam(heap_t* heap){
    if(heap->cantidad == heap->capacidad){
        size_t nuevo_tam = (heap->capacidad)*2;
        if (!redimensionar(heap,nuevo_tam)){
            return false;
        }
    }
    else if(((heap->cantidad)*4 <= (heap->capacidad)) && (heap->capacidad >10)){
        size_t nuevo_tam = (heap->capacidad)/2;
        if (!redimensionar(heap,nuevo_tam)){
            return false;
        }
    }
    return true;
}

void swap (void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

void upheap(void** arreglo, cmp_func_t cmp, size_t pos){
    if(pos == 0){
        return;
    }

    size_t posc_padre = (pos-1)/2;
    if(cmp(arreglo[pos], arreglo[posc_padre]) < 0){
        return;
    }
    swap(&arreglo[pos], &arreglo[posc_padre]);
    upheap(arreglo, cmp, posc_padre);
}

void downheap(void** arreglo, size_t cantidad, size_t pos_padre, cmp_func_t cmp){
    if(pos_padre >= cantidad) return;
    size_t hijo_izq = (2*pos_padre)+1;
    size_t hijo_der = (2*pos_padre)+2;
    size_t pos_max = pos_padre;
    if(hijo_izq < cantidad && cmp(arreglo[hijo_izq], arreglo[pos_padre]) > 0){
        pos_max = hijo_izq;
    }
    if(hijo_der < cantidad && cmp(arreglo[hijo_der], arreglo[pos_padre]) > 0){
        pos_max = hijo_der;
    }
    if(pos_padre != pos_max)
    swap(&arreglo[pos_padre], &arreglo[pos_max]);
    downheap(arreglo, cantidad, pos_max, cmp);
}

void heapify(void** arreglo, size_t cantidad, cmp_func_t cmp){
    for(size_t i = cantidad; i > 0; i-- )
    downheap(arreglo,i,i/2, cmp);
}
