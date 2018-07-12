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
		if lines.isnumeric():
			mode = mode + 1
		elif mode == 1:
			data = lines.split(',')
			grafo.agregar_vertice(data[0])
		elif mode == 2:
			data = lines.split(',')
			grafo.agregar_arista(data[0],data[1],data[2])

print('OK')
print('grafo creado')

lista = camino_minimo(grafo, 'Moscu', 'Sochi')
print (lista)
