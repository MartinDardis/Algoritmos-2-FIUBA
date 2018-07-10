class Grafo:

    def __init__(self):
        """Crea un grafo vacio."""
        self.vertices = {}

    def agregar_vertice(self, v):
        """Agrega el vertice """
        self.vertices[v] = {}

    def destruir_vertice(self, v):
        """Destruye el vertice x."""
        self.vertices.pop(v)

    def agregar_arista(self, desde, hasta, peso):
        """Agrega un arista"""
        diccionario = self.vertices.pop(desde)
        diccionario[hasta] = peso
        self.vertices[desde] = diccionario

    def destruir_arista(self, desde, hasta):
        diccionario = self.vertices.pop(desde)
        diccionario.pop(hasta)
        self.vertices[desde] = diccionario

    def adyacentes(self, v):
        return self.vertices[v].values

    def grado_salida(self, v):
        return len(self.adyacentes(v))

    def grado_entrada(self, v):
        contador = 0
        for w in self.vertices:
            if self.hay_arista(w, v):
                contador += 1;
        return contador
