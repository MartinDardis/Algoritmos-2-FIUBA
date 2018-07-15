
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
	j = ' -> ' #Este es el separador
	crear_kml(lista,city_coord,map_file)
	salida = j.join(lista)
	salida += '\nCosto total: ' + str(peso)
	print(salida)

def viaje_optimo (grafo,origen):
	lista, peso = viajante_backtracing(grafo,origen)
	j = ' -> ' #Este es el separador
	crear_kml(lista[0],city_coord,map_file)
	salida = j.join(lista[0])
	salida += '\nCosto total: ' + str(peso)
	print(salida)

def viaje_aproximado(grafo,origen):
	lista, peso = viajante_backtracing(grafo,origen)
	j = ' -> ' #Este es el separador
	crear_kml(lista[0],city_coord,map_file)
	salida = j.join(lista[0])
	salida += '\nCosto total: ' + str(peso)
	print(salida)

def itinerario(grafo,archivo):
	grafo_topo = hacer_grafo_topologico(grafo,archivo)
	lista = orden_topologico(grafo_topo)
	print(lista)
	crear_kml_de_grafo(lista,map_file)
	j = ' -> ' #Este es el separador
	salida = j.join(lista[0])
	salida += '\nCosto total: ' + str(peso)
	print(salida)

def reducir_caminos(grafo,archivo):
	mst, peso = arbol_tendido_minimo(grafo)
	crear_csv(grafo,mst,city_coord,archivo)
	print('Peso total: '+str(peso))

entrada = input()
while len(entrada) > 0:
	entrada = entrada.rstrip()
	entrada = entrada.replace(',',"")
	spl = entrada.split( )
	if spl[0] == 'ir':
		camino(grafo,spl[1],spl[2])
	elif spl[0] == 'viaje' and  spl[1] == 'optimo':
		viaje_optimo(grafo,spl[2])
	elif spl[0] == 'viaje' and spl[1] == 'aproximado':
		viaje_aproximado(grafo,spl[2])
	elif spl[0] == 'itinerario':
		itinerario(grafo,spl[1])
	elif spl[0] == 'reducir_caminos':
		reducir_caminos(grafo,spl[1])
	else:
		print('ERROR en comando' + spl[0])
	entrada = input('')
