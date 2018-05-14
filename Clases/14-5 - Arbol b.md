## Arbol B

#### Tiempos
* Buscar -> O(log n))
* Insertar -> O(log n)
* Borrar -> O(log n)

#### Caracteristicas
* Poca altura y muchos hijos
* Cantidad de claves por nodo (Todo nodo lleno entre 50% y 100%)
  * **K** = Max claves en nodo
  * **M = k+1** Max hijos por nodo
  * **K/2** = MIN claves en hijo.
    * Para **B***, **2K/3** = MIN claves en hijo. (66% -100%).

### Funcionamiento
* **Buscar:** Igual que un abb.
* **Insertar:** Agrego hasta llenar la raiz, cuando hago un **overflow** ( lleno la raiz ).
 * Agarro la mitad, lo subo y hago un split con los menors a la mitad y los mayores
* **Borrar:** Busco
  * Hoja? Borro.
  * No Hoja? Swap con el inferior y Borro
  * **Underflow**? Redistribuir y join
