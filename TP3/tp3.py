from cola import *
from pila import *
from heap import *
from grafo import *

def todos_visitados(vertices, visitados):
    for u in vertices:
        if u not in visitados:
            return False
    return True

def hacer_grafo_topologico(grafo, topologic_file):
    grafo_topologico = Grafo(grafo.vertices)
    visitados = []
    with open(topologic_file,'r') as cities:
        mode = 0
        for lines in cities:
            data = lines.split(',')
            data[1] = data[1].rstrip()
            grafo_topologico.agregar_arista_simple(data[0], data[1], grafo.peso_arista(data[0], data[1]))
            if data[0] not in visitados:
                visitados.append(data[0])
            if data[1] not in visitados:
                visitados.append(data[1])
    return grafo_topologico

def orden_topologico(grafo):
    visitados = []
    grados = {}
    pila = Pila()
    for v in grafo.vertices:
        grados[v] = grafo.grado_entrada(v)
    for v in grafo.vertices:
        if v not in visitados and grados[v] == 0:
            orden_topologico_dfs(grafo, v, pila, visitados, grados)
    lista= pila.pila_a_lista()
    lista = lista[::-1]
    return lista

def orden_topologico_dfs(grafo, v, pila, visitados, grados):
    pila.apilar(v)
    visitados.append(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            grados[w] -= 1
            if grados[w] == 0:
                orden_topologico_dfs(grafo, w, pila, visitados, grados)


def camino_minimo(grafo, origen, fin):
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
    peso_total = 0
    while v != None:
        pila.apilar(v)
        if padre[v] != None:
            peso_total += grafo.peso_arista(v, padre[v])
        v = padre[v]

    lista = pila.pila_a_lista()
    return lista, peso_total

def mst_prim(grafo, inicio):
    visitados = []
    visitados.append(inicio)
    heap = Heap()

    for v in grafo.vertices:
        for w in grafo.adyacentes(v):
            arista = Arista(v, w, grafo.peso_arista(v,w))
            heap.encolar(arista)

    arbol = Grafo(grafo.vertices)

    while not heap.esta_vacia():
        arista = heap.desencolar()
        if arista.destino in visitados:
            continue
        arbol.agregar_arista_doble(arista.origen, arista.destino, arista.peso)
        visitados.append(arista.destino)

    peso_total = 0
    for v in arbol.vertices:
        for w in arbol.adyacentes(v):
            peso_total += arbol.peso_arista(v, w)
    return arbol, peso_total

def viajante_backtracing(grafo, inicio):
    visitados = []
    minimo = 99999 #infinito
    peso_actual = 0
    resultados = []
    pila = Pila()
    pila.apilar(inicio)
    peso = 0
    minimo = viajante_backtracing_recursivo(grafo, inicio, inicio, visitados, peso, minimo, pila, resultados)
    return resultados, minimo

def viajante_backtracing_recursivo(grafo, inicio, v, visitados, peso, minimo, pila, resultados):
    visitados.append(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            peso += grafo.peso_arista(v, w)
            if peso < minimo:
                pila.apilar(w)
                minimo = viajante_backtracing_recursivo(grafo, inicio, w, visitados, peso, minimo, pila, resultados)
                pila.desapilar()
            peso -= grafo.peso_arista(v, w)

    if todos_visitados(grafo.vertices, visitados):
        peso += grafo.peso_arista(inicio, pila.ver_tope())
        if peso <= minimo:
            pila.apilar(inicio)
            lista = pila.pila_a_lista()
            if peso < minimo:
                minimo = peso
                while len(resultados) > 0:
                    resultados.pop()
            resultados.append(lista)
            pila.desapilar()
        peso -= grafo.peso_arista(inicio, pila.ver_tope())
    visitados.remove(v)
    return minimo

def viajante_greedy(grafo, inicio):
    visitados = []
    pila = Pila()
    pila.apilar(inicio)
    visitados.append(inicio)
    peso_total = 0
    v = inicio
    while not todos_visitados(grafo.vertices, visitados):
        minimo = 99999 #infinito
        for w in grafo.adyacentes(v):
            if w not in visitados:
                if grafo.peso_arista(v, w) < minimo:
                    minimo = grafo.peso_arista(v, w)
                    vertice = w
        peso_total += minimo
        pila.apilar(vertice)
        visitados.append(vertice)
        v = vertice
    peso_total += grafo.peso_arista(vertice, inicio)
    pila.apilar(inicio)
    lista = pila.pila_a_lista()
    return lista, peso_total

def crear_kml(salida,city_coord,map_file):
    with open(map_file,'w') as archivo:
        archivo.write('<?xml version="1.0" encoding="UTF-8"?>\n')
        archivo.write('<kml xmlns="http://earth.google.com/kml/2.1">\n')
        archivo.write('<Document>\n')
        archivo.write('<name>KML</name>\n')
        for s in salida:#coloca las ciudades
            archivo.write('\t<Placemark>\n')
            archivo.write('\t<name>'+s+'</name>\n')
            archivo.write('\t\t<Point>\n')
            archivo.write('\t\t\t<coordinates>'+city_coord[s]+'</coordinates>\n')
            archivo.write('\t\t</Point>\n')
            archivo.write('\t</Placemark>\n')
        ant = None
        for s in salida:
            if ant == None:
                ant = s
            else:
                archivo.write('\t<Placemark>\n')
                archivo.write('\t\t<LineString>\n')
                archivo.write('\t\t\t<coordinates>'+city_coord[ant]+' '+city_coord[s]+'</coordinates>\n')
                archivo.write('\t\t</LineString>\n')
                archivo.write('\t</Placemark>\n')
                ant = s
        archivo.write('</Document>\n')
        archivo.write('</kml>\n')
