## Heapify
* Recibe un arreglo de elementos genericos
* Devuelve un arreglo hecho Heapify
* Orden O(n)

#### Proceso
1. Hacer **Downheap** de las hojas hacia la raiz. (En las hojas no se realiza downheap porque no tiene hijos)
  * Se podria hacer solo de la mitad del arreglo para adelante
---
## Heap-Sort

* Recibe un arreglo
* Devuelve un arreglo ordenado
* Orden: O(n*log(n))

#### Proceso

*  Recibo un Heap

Hago el siguiente ciclo hasta que el tope sea 1
  1.  Cambio EL PRIMER ELEMENTO con el ULTIMO
  2.  Disminuyo 1 el tope
  3.  Hago downheap

|    Entrada     | --> |        Salida           |
|------------------------------------------------|
|Heap de maximos | --> | arreglo de menor a mayor|
|Heap de minimos | --> | Arreglo de mayor a menor|

---
#### Ejercicio:
Dados 3 arreglos, unirlos y devolver 1 ordenado de menor a mayor en O(n*log(k))
`{5,10,15,20}   {11,13,16,19}   {2,26,40,45}`

`int* k_merge(int* *arr,size_t k, size_t h)`
