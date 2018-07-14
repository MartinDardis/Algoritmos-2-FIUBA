class Arista:

    def __init__(self, origen, destino, peso):
        self.origen = origen
        self.destino = destino
        self.peso = peso

    def __lt__(self, other):
        return self.peso>other.peso

    def __gt__(self, other):
        return self.peso<other.peso

    def __eq__(self, other):
        return self.peso==other.peso

    def origen(self):
        return self.origen

    def destino(self):
        return self.destino

    def peso(self):
        return self.peso

    def __str__(self):
        return (str(self.origen) + ', ' + str(self.destino) + ', ' + str(self.peso))

class Grafo:

    def __init__(self, vertices = None, copiar_aristas = False):
        """Crea un grafo vacio."""
        self.vertices = {}
        if vertices != None:
            if copiar_aristas == False:
                for v in vertices:
                    self.vertices[v] = {}
            else:
                self.vertices = vertices

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

    def destruir_arista_simple(self, desde, hasta):
        diccionario = self.vertices.pop(desde)
        diccionario.pop(hasta)
        self.vertices[desde] = diccionario

    def destruir_arista_doble(self, desde, hasta):
        diccionario = self.vertices.pop(desde)
        diccionario.pop(hasta)
        self.vertices[desde] = diccionario
        diccionario = self.vertices.pop(hasta)
        diccionario.pop(desde)
        self.vertices[hasta] = diccionario

    def hay_arista(self, desde, hasta):
        for v in self.vertices[desde]:
            if hasta == v:
                return True
        return False

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
