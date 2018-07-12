from cola import *
from pila import *
from heap import *
from grafo import *

def orden_topologico(grafo):
    visitados = set()
    grados = {}
    pila = Pila()
    for v in grafo.vertices():
        grados[v] = grafo.grado_entrada(v)
    for v in grafo.vertices():
        if v not in visitados and grados[v] == 0:
            orden_topologico_dfs(grafo, v, pila, visitados, grados)
    return pila_a_lista(pila)

def orden_topologico_dfs(grafo, v, pila, visitados, grados):
    pila.apilar(v)
    visitados.agregar(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            grados[w] -= 1
            if grados[w] == 0:
                orden_topologico_dfs(grafo, w, pila, visitados)

def camino_minimo(grafo, origen, fin):
    print('llegue')
    dist = {}
    padre = {}
    for v in grafo.vertices:
        dist[v] = 99999 #infinito
    dist[origen] = 0
    padre[origen] = None
    heap = Heap()
    heap.encolar(origen)
    while not heap.esta_vacia():
        v = heap.desencolar()
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso_arista(v, w) < dist[w]:
                padre[w] = v
                dist[w] = dist[v] + grafo.peso_arista(v,w)
                heap.encolar(w)

    pila = Pila()
    v = fin
    while v != inicio:
        pila.apilar(v)
        v = padre[v]

    lista = []
    for i in range(len(pila)):
        lista.append[pila.desapilar()]
    return lista

def mst_prim(grafo, inicio):
    visitados = set()
    visitados.agregar(inicio)
    heap = Heapq()
    for w in grafo.adyacentes(inicio):
        heap.encolar((inicio, w), grafo.peso_arista(inicio,w))
    arbol = Grafo(grafo.vertices)
    while not heap.esta_vacia():
        (v, w) = heap.desencolar()
        if w in visitados:
            continue
        argol.agregar_arista(v, w, grafo.peso_arista(v, w))
        visitados.agregar(w)
        for u in grafo.adyacentes(w):
            heap.encolar((w, u), grafo.peso_arista(w, u))
    return arbol

def viajante_backtracing(grafo, inicio):
    visitados = set()
    minimo = 99999 #infinito
    peso_actual = 0
    resultados = set()
    pila = Pila()
    viajante_backtracing_recursivo(grafo, inicio, inicio, visitados, peso, minimo, pila, resultados)
    return resultados

def viajante_backtracing_recursivo(grafo, inicio, v, visitados, peso, minimo, pila, resultados):
    visitados.append(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            peso += peso_arista(v, w)
            if peso < minimo:
                pila.apilar(w)
                viajante_backtracing_recursivo(grafo, inicio, w, visitados, peso, minimo, pila, resultados)
                pila.desapilar()
            peso -= peso_arista(v, w)

    todos_visitados = true
    for u in grafo.vertices():
        if u not in visitados:
            todos_visitados = false

    if todos_visitados:
        pila.apilar(inicio)
        lista = pila_a_lista(pila)
        if peso < minimo:
            while len(resultados) > 0:
                resultados.pop()
        resultados.append(lista)
    visitados.remove(v)

def viajante_greedy(grafo, inicio):
    visitados = set()
    pila = Pila()
    v = inicio
    while v not in todos_visitados:
        visitados.append(v)
        minimo = 99999 #infinito
        for w in grafo.adyacentes(v):
            if peso_arista(v, w) < minimo:
                minimo = peso_arista(v, w)
                vertice = w
        pila.apilar(w)
        v = w
    pila.apilar(inicio)
    lista = pila_a_lista(pila)
    return lista
