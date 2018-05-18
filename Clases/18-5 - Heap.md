## Heap
**Es arbol que en la raiz tiene mas prioridad de salida que sus hijos**

#### Propiedades de heap
* **hijo_izq** = 2*pos + 1
* **hijo_der** = 2*pos + 2
* **padre** = (pos-1)/2
* **ultimo_padre** = (largo/2)-1
* **raiz** = (el_mas_grande / chico) = 0
#### Funcionamiento
* **Upheap:** Mientras un elemento sea menor que su padre van swapeando (encolar)
* **Downheap:**

#### Estructura de heap
``` C
struct heap{
  size_t cant;
  void** datos;
  size_t cap;
  cmp_func_t comparar;
}
```
#### Primitivas
* **Encolar / UPHEAP:**
  1. Agregar el elemento en la posc_final+1
  2. Llamar a **UPHEAP** para ese elemento a Agregar
    * Calcular la posc del padre
    * Se pregunta si se cumple la cond de heap
``` c
void upheap(heap_t* arreglo,size_t pos,cmp_func_t* cmp)
  if(pos == 0) return;
  size_t padre = (pos-1)/2;
  if(cmp(arreglo[pos],areglo[padre])<0) return;
  swap(arreglo[pos],areglo[padre]);
  upheap(arreglo,padre,cmp);
```

* **Descolar/Downheap:**
  1. Se elimina el primero del arreglo y se considera al ultimo como primero/raiz
  2. Llamo a **DOWNHEAP** para ese elemento
    * Calcular la pos de ambos hijos
    * Se pregunta si cumple la cond de heap, termina, sino se swapea el padre con su hijo_menor.
``` c
void downheap(heap_t* arreglo,size_t n,size_t pos /*padre*/,cmp_func_t* cmp){
  if( pos >= n) return;
  size_t hijo_izq = 2*pos + 1;
  size_t hijo_der = 2*pos + 2;
  size_t pos_max = pos;
  if( hijo_izq < n && cmp (arreglo[hijo_izq]),arreglo[max]>0){
    pos_max = hijo_izq;
  }
  if( hijo_der > n && cmp (arreglo[hijo_der]),arreglo[max]>0){
    pos_max = hijo_der;
  }
  if(pos != pos_max)
    swap();
    downheap(arreglo,n,pos_max,cmp);
}
```

---
## Ejercicio
```c
void print_k_longest(const char* cadenas [],int k,int tope){
  heap_t* heap_aux = heap_crear(cmp);
  for(int i=0;i<k;i++){
    heap_encolar(heap_aux,cadenas[i]);
  }
  for(int i=k;i<tope;i++){
    if(cmp(cadenas[i],heap_ver_min(heap_aux))){
      heap_desencolar(heap_aux);
      heap_encolar(heap_aux,cadenas[i]);
    }
  while(!heap_esta_vacio(heap_aux))
    printf("%s\n",heap_desencolar(heap_aux));
  }
  heap_destruit(heap_aux;NULL);
}
```
