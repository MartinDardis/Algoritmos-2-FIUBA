
from sys import *
from tp3 import *
from grafo import *

city_file = argv[1]
map_file = argv[2]
city_coord = {}
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
camino(grafo, 'Moscu', 'Sochi')

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


def camino (grafo,desde,hasta):
	lista, peso = camino_minimo(grafo,desde,hasta)
	salida = []
	for i in range(0,len(lista)):
		salida.append(lista[i])
	j = ' -> ' #Este es el separador
	salida = j.join(salida)
	salida += '\nCosto total: ' + str(peso)
	print(salida)

def viaje_optimo:

entrada = input()
while len(entrada) > 0:
	spl = entrada.split( )
	if spl[0] == 'ir':
		camino(grafo,spl[1],spl[2])
	elif spl[0] == 'viaje' or  spl[0] == 'viaje aproximado':
		viaje_optimo(grafo,spl[2])
	elif spl[0] == 'itinerario':
		intinerario(grafo,spl[2])
	elif spl[0] == 'reducir_caminos':
		reducir_caminos(grafo,spl[2])
	else:
		print('ERROR en comando' + spl[0])
	entrada = input('')
