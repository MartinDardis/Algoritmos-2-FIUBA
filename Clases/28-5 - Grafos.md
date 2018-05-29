## Grafos

### Formas de representacion:

* **Matriz de incidencia:** (Vertices y aristas).
Si el grado es no dirigido, no hay pesos negativos porque no hay direccion

|   |A|B|C|D|
|-----------|
|A1|-1|1|0|0|
|A2|0|-1|1|0|
|A3|-1|0|0|1|

* **Matriz de adyacencia:**(Vertices y vertices)

| |A|B|C|D|
|---------|
|A|**0**|1|0|1|
|B|0|**0**|1|0|
|C|0|0|**0**|0|
|D|0|0|0|**0**|

Nota: Si la diagonal es **0** el grafo es simple. Sino es complejo

* **Lista de adyacencias:** (lista de listas)

||
|-|
|A|->|B|->|C|
||
|B|->|C|
||
|C|N/A|
||
|D|N/A|

* **DIiccionario de diccionarios:**

|A:|{B:"*peso*",D:"*peso*"}||B:|{C:"*peso*"}||C:|{}||D:|{}
|--------------|
|Clave|Datos   |

### Ordenes de tiempo:

||Memoria|Agregar Vertice|Agregar Arista|Ver Conn entre nodos|Sacar Vertice|Sacar Arista|
|----|
|M. incidencia|O(V*E)|O(VxE)|O(VxE)|O(E)|O(V*E)|O(V*E)|
|M. adyacencias|O(V²)|O(V²)|O(1)|O(1)|O(V²)|O(1)|
|Lista adyacencias|O(V+E)|O(1)|O(V)|O(V²)|O(V+E)|O(V)|
|Diccionario de Diccionario|O(V+E)|O(1)|O(1)|O(1)|O(V)|O(1)
