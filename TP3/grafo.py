class Arista:

    def __init__(self, origen, destino, peso):
        self.origen = origen
        self.destino = destino
        self.peso = peso

    def __lt__(self, other):
        return self.peso<other.peso

    def __gt__(self, other):
        return self.peso>other.peso

    def __eq__(self, other):
        return self.peso==other.peso

    def origen(self):
        return self.origen

    def destino(self):
        return self.destino

    def peso(self):
        return self.peso

class Grafo:

    def __init__(self, vertices = None):
        """Crea un grafo vacio."""
        self.vertices = {}
        if vertices != None:
            for v in vertices:
                self.vertices[v] = {}

    def agregar_vertice(self, v):
        """Agrega el vertice """
        self.vertices[v] = {}

    def destruir_vertice(self, v):
        """Destruye el vertice x."""
        self.vertices.pop(v)

    def agregar_arista_simple(self, desde, hasta, peso):
        """Agrega un arista"""
        self.vertices[desde][hasta] = peso

    def agregar_arista_doble(self, desde, hasta, peso):
        """Agrega un arista"""
        self.vertices[desde][hasta] = peso
        self.vertices[hasta][desde] = peso

    def destruir_arista(self, desde, hasta):
        diccionario = self.vertices.pop(desde)
        diccionario.pop(hasta)
        self.vertices[desde] = diccionario

    def adyacentes(self, v):
        return self.vertices[v].keys()

    def grado_salida(self, v):
        return len(self.adyacentes(v))

    def grado_entrada(self, v):
        contador = 0
        for w in self.vertices:
            if self.hay_arista(w, v):
                contador += 1;
        return contador

    def peso_arista(self, desde, hasta):
        return self.vertices[desde][hasta]

    def __str__(self):
        string = str()
        for v in self.vertices:
            string += str(v + ':\n')
            string += str(self.vertices[v])
            string += '\n\n'
        return string
