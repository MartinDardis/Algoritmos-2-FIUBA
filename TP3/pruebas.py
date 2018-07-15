
from sys import *
from tp3 import *
from grafo import *


city_file = argv[1]
map_file = argv[2]
topologic_file = 'ejemplo_recomendaciones.csv'

grafo = Grafo()

with open(city_file,'r') as cities:
    mode = 0
    for lines in cities:
        if lines[0].isnumeric():
            mode = mode + 1
        elif mode == 1:
            data = lines.split(',')
            grafo.agregar_vertice(data[0])
        elif mode == 2:
            data = lines.split(',')
            grafo.agregar_arista_doble(data[0],data[1],int(data[2]))

print('\033[92m grafo \033[0m')
print(grafo)
print('\033[92m Camino minimo entre Moscu y Sochi \033[0m')
lista, peso = camino_minimo(grafo, 'Moscu', 'Sochi')
mostrar_resultado(lista, peso)

print('\033[92m Arbol de tendido minimo \033[0m')
arbol, peso = arbol_tendido_minimo(grafo)
print(peso)
print(arbol)

print('\033[92m Viajante \033[0m')
lista_de_listas, peso = viajante(grafo, 'Moscu')
mostrar_resultado(lista_de_listas[0], peso)

print('\033[92m Viajante aproximado \033[0m')
lista, peso = viajante_aproximado(grafo, 'Moscu')
mostrar_resultado(lista, peso)

print('\033[92m Orden topologico \033[0m')
grafo_topologico = hacer_grafo_topologico(grafo, topologic_file)
lista = orden_topologico(grafo_topologico)
peso = conseguir_peso(grafo, lista)
mostrar_resultado(lista, peso)
