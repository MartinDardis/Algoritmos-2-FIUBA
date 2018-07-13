from cola import *
from pila import *
from heap import *
from grafo import *

def orden_topologico(grafo):
    visitados = set()
    grados = {}
    pila = Pila()
    for v in grafo.vertices:
        grados[v] = grafo.grado_entrada(v)
    for v in grafo.vertices:
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
    while v != None:
        pila.apilar(v)
        v = padre[v]

    lista = pila.pila_a_lista()
    return lista

def mst_prim(grafo, inicio):
    visitados = []
    visitados.append(inicio)
    heap = Heap()

    for v in grafo.adyacentes(inicio):
        arista = Arista(inicio, v, grafo.peso_arista(inicio,v))
        heap.encolar(arista)

    arbol = Grafo(grafo.vertices)

    while not heap.esta_vacia():
        arista = heap.desencolar()
        if arista.destino in visitados:
            continue
        arbol.agregar_arista_doble(arista.origen, arista.destino, arista.peso)
        visitados.append(arista.destino)

        for w in grafo.adyacentes(arista.destino):
            arista = Arista(arista.destino, w, grafo.peso_arista(arista.destino, w))
            heap.encolar(arista)

    return arbol

def viajante_backtracing(grafo, inicio):
    visitados = []
    minimo = 99999 #infinito
    peso_actual = 0
    resultados = []
    pila = Pila()
    pila.apilar(inicio)
    peso = 0
    viajante_backtracing_recursivo(grafo, inicio, inicio, visitados, peso, minimo, pila, resultados)
    return resultados

def viajante_backtracing_recursivo(grafo, inicio, v, visitados, peso, minimo, pila, resultados):
    visitados.append(v)
    print('\033[91m' + str(visitados) + '\033[0m')
    for w in grafo.adyacentes(v):
        if w not in visitados:
            peso += grafo.peso_arista(v, w)
            if peso < minimo:
                pila.apilar(w)
                print('\033[94m' + str(w) + '\033[0m' + ' ' + str(pila))
                viajante_backtracing_recursivo(grafo, inicio, w, visitados, peso, minimo, pila, resultados)
                #print(pila)
                pila.desapilar()
            peso -= grafo.peso_arista(v, w)

    todos_visitados = True
    for u in grafo.vertices:
        if u not in visitados:
            todos_visitados = False

    if todos_visitados:
        pila.apilar(inicio)
        lista = pila.pila_a_lista()
        if peso < minimo:
            while len(resultados) > 0:
                resultados.pop()
        resultados.append(lista)
    visitados.remove(v)

def viajante_greedy(grafo, inicio):
    visitados = []
    pila = Pila()
    v = inicio
    while v not in visitados:
        visitados.append(v)
        minimo = 99999 #infinito
        for w in grafo.adyacentes(v):
            if grafo.peso_arista(v, w) < minimo:
                minimo = grafo.peso_arista(v, w)
                vertice = w
        pila.apilar(w)
        v = w
    pila.apilar(inicio)
    lista = pila.pila_a_lista()
    return lista

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
		archivo.write('</Document>\n')
		archivo.write('</kml>\n')
