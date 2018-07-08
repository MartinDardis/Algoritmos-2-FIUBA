class Heap:
    """Representa a una cola, con operaciones de encolar y
    desencolar. El primero en ser encolado es también el primero
    en ser desencolado."""

    def __init__(self):
        """Crea una cola vacía."""
        self.items = []

    def esta_vacia(self):
        """Devuelve True si la cola esta vacía, False si no."""
        return len(self.items) == 0

    def swap(a, b):
        c = a
        a = b
        b = c
        return;

    def upheap(self, posc):
        if(posc = 0):
            return
        posc padre = (posc-1)/2
        if self.items[pos] < self.items[posc_padre]:
            return
        }
        swap(self.items[pos], self.items[posc_padre])
        upheap(self, posc_padre)

    def downheap(self, posc_padre):
        cantidad = len(self.items)
        if pos_padre >= cantidad:
            return
        hijo_izq = (2*pos_padre)+1
        hijo_der = (2*pos_padre)+2
        pos_max = pos_padre
        if hijo_izq < cantidad and arreglo[hijo_izq] > arreglo[pos_max]:
            pos_max = hijo_izq
        }
        if hijo_der < cantidad and arreglo[hijo_der] > arreglo[pos_max]:
            pos_max = hijo_der
        }
        if pos_padre == pos_max:
            return
        }
        swap(arreglo[pos_padre], arreglo[pos_max])
        downheap(self, pos_max)


    def encolar(self, x):
        """Encola el elemento x."""
        self.items.append(x)
        upheap(self, len(self.items))

    def desencolar(self):
        """Elimina el primer elemento de la cola y devuelve su
        valor. Si la cola está vacía, levanta ValueError."""
        if self.esta_vacia():
            raise ValueError("La cola está vacía")
        swap(self.items[0], self.items[len(self.items)])
        valor = self.items.pop()
        downheap(self, 0)
        return valor
