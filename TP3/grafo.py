class Grafo:
    """Representa a una cola, con operaciones de encolar y
    desencolar. El primero en ser encolado es también el primero
    en ser desencolado."""

    def __init__(self):
        """Crea un grafo vacio."""
        self.vertices = {}

    def agregar_vertice(self, v):
        """Agrega el vertice v."""
        self.vertices[v] = {}

    def destruir_vertice(self, v):
        """Destruuye el vertice x."""
        self.vertices.pop(v)

    def agregar_arista(self, desde, hasta, peso):
        """Agrega el vertice x."""
        diccionario = self.vertices.pop(desde)
        diccionario[hasta] = peso
        self.vertices[desde] = diccionario

    def destruir_arista(self, desde, hasta):
        """Destruuye el vertice x."""
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
