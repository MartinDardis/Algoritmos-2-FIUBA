

def orden_topologico(grafo):
    visitados = set()
    pila = pila_crear()
    for v in grafo.vertices:
        if v not in visitados:
            orden_topologico_dfs(grafo, v, pila, visitados)
    return pila_a_lista(pila)

def orden_topologico_dfs(grafo, v, pila, visitados):
    visitados.agregar(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden_topologico_dfs(grafo, w, pila, visitados)
    pila_apilar(v)

def camino_minimo(grafo, origen):
    dist = {}
    padre = {}
    for v in grafo.vertices:
        dist[v] = #infinito
    dist[origen] = 0
    padre[origen] = none
    q = heap_crear()
    q.encolar[origen, dist[origen]]
    while not q.esta_vacia():
        v = q_desencolar()
        for w in grafo.adyacentes(v):
            if dist[v]+grado.peso_arista(v, w) < dist[w]
                padre[w] = v
                dist[w] = dist[v]+grafo.peso_arista(v,w)
                q.encolar(w, dist[w])
    return padre, dist

def mst_prim(grafo, inicio):
    visitados = set()
    visitados.agregar(inicio)
    q = heap_crear()
    for w in grafo.adyacentes(inicio)
        q.encolar((inicio, w), grafo.peso_arsta(inicio,w))
    arbol = grafo_crear(grafo.vertices)
    while not q.esta_vacia():
        (v, w) = q.desencolar()
        if w in visitados:
            continue
        argol.agregar_arista(v, w, grafo.peso_arista(v, w))
        visitados.agregar(w)
        for u in grafo.adyacentes(w)
            q.encolar((w, u), grafo.peso_arista(w, u))
    return arbol
