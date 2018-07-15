
from sys import *
from tp3 import *
from grafo import *

city_file = argv[1]
map_file = argv[2]
city_coord = {}

grafo = Grafo()

with open(city_file,'r') as cities:
	mode = 0
	for lines in cities:
		lines = lines.rstrip()
		if lines[0].isnumeric():
			mode = mode + 1
		elif mode == 1:
			data = lines.split(',')
			grafo.agregar_vertice(data[0])
			data[2] = data[2].replace('\n',"")
			city_coord[data[0]]=(data[1]+', '+data[2])
		elif mode == 2:
			data = lines.split(',')
			grafo.agregar_arista_doble(data[0],data[1],int(data[2]))


def camino (grafo,desde,hasta):
	lista, peso = camino_minimo(grafo,desde,hasta)
	mostrar_resultado(lista, peso)
	crear_kml(lista,city_coord,map_file)

def viajante_backtracking (grafo,origen):
	lista_de_listas, peso = viajante(grafo,origen)
	mostrar_resultado(lista_de_listas[0], peso)
	crear_kml(lista_de_listas[0],city_coord,map_file)

def viajante_greedy(grafo,origen):
	lista, peso = viajante_aproximado(grafo,origen)
	mostrar_resultado(lista, peso)
	crear_kml(lista,city_coord,map_file)

def itinerario(grafo,archivo):
	grafo_topo = hacer_grafo_topologico(grafo,archivo)
	lista = orden_topologico(grafo_topo)
	peso = conseguir_peso(grafo, lista)
	mostrar_resultado(lista, peso)
	crear_kml(lista,city_coord,map_file)

def reducir_caminos(grafo,archivo):
	mst, peso = arbol_tendido_minimo(grafo)
	crear_csv(mst,city_coord,archivo)
	print('Peso total: '+str(peso))

entrada = input()
while len(entrada) > 0:
	entrada = entrada.rstrip()
	entrada = entrada.replace(',',"")
	spl = entrada.split( )
	if spl[0] == 'ir':
		camino(grafo,spl[1],spl[2])
	elif spl[0] == 'viaje' and  spl[1] == 'optimo':
		viajante_backtracking(grafo,spl[2])
	elif spl[0] == 'viaje' and spl[1] == 'aproximado':
		viajante_greedy(grafo,spl[2])
	elif spl[0] == 'itinerario':
		itinerario(grafo,spl[1])
	elif spl[0] == 'reducir_caminos' or 'reducir caminos':
		reducir_caminos(grafo,spl[1])
	else:
		print('ERROR en comando' + spl[0])
	entrada = input('')
