
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
			city_coord[data[0]]=(data[1],data[2])
		elif mode == 2:
			data = lines.split(',')
			grafo.agregar_arista_doble(data[0],data[1],int(data[2]))




print('\033[92m grafo \033[0m')
print(grafo)
print('\033[92m Camino minimo entre Moscu y Sochi \033[0m')
lista_peso = camino_minimo(grafo, 'Moscu', 'Sochi')
print str(peso + '\n' + str(lista))

print('\033[92m Arbol de tendido minimo \033[0m')
arbol, peso = mst_prim(grafo, 'Moscu')
print(peso)
print(arbol)

print('\033[92m Viajante \033[0m')
lista, peso = viajante_backtracing(grafo, 'Moscu')
print(peso)
for i in lista:
	print(i)

print('\033[92m Viajante aproximado \033[0m')
lista, peso = viajante_greedy(grafo, 'Moscu')
print(peso)
print(lista)

grafo_topologico = hacer_grafo_topologico(grafo, topologic_file)
print(grafo_topologico)
lista = orden_topologico(grafo_topologico)
print(lista)
