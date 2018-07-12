from sys import argv
from tp3 import *
from grafo import *


city_file = argv[1]
map_file = argv[2]

grafo = Grafo()
with open(city_file,'r') as cities:
	mode = 0
	for lines in cities:
		print (lines)
		if lines[0].isnumeric():
			mode = mode + 1
		elif mode == 1:
			data = lines.split(',')
			grafo.agregar_vertice(data[0])
		elif mode == 2:
			data = lines.split(',')
			grafo.agregar_arista_doble(data[0],data[1],int(data[2]))

print('\033[92m grafo\n \033[0m')
print(grafo)
print('\033[92m Camino minimo entre Kaliningrado y Nizhni Novgorod\n \033[0m')
lista = camino_minimo(grafo, 'Kaliningrado', 'Nizhni Novgorod')
print (lista)

print('\033[92m Arbol de tendido minimo\n \033[0m')
arbol = mst_prim(grafo, 'Moscu')
print(arbol)

print('\033[92m Viajante\n \033[0m')
lista = viajante_backtracing(grafo, 'Moscu')
print(lista)

print('\033[92m Viajante aproximado\n \033[0m')
lista = viajante_greedy(grafo, 'Moscu')
print(lista)
