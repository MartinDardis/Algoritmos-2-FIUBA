
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
	lista = camino_minimo(grafo,desde,hasta)
	salida = []
	anterior = 0
	peso = 0
	for i in range(0,len(lista)):
		salida.append(lista[i])
		if not anterior == 0:
			peso += grafo.peso_arista(anterior,lista[i])
		anterior = lista[i]
	j = ' -> ' #Este es el separador
	crear_kml(salida,city_coord,map_file)
	salida = j.join(salida)
	print(salida)
	print('Costo total: ' + str(peso))

def viaje_optimo (grafo,origen):
	print('ok')
def viaje_aproximado(grafo,origen):
	print('ok')
def itinerario(grafo,archivo):
	print('ok')
def reducir_caminos(grafo,archivo):
	print('ok')

entrada = input()
while len(entrada) > 0:
	entrada = entrada.replace(',',"")
	spl = entrada.split( )
	if spl[0] == 'ir':
		camino(grafo,spl[1],spl[2])
	elif spl[0] == 'viaje' and  spl[1] == 'optimo,':
		viaje_optimo(grafo,spl[2])
	elif spl[0] == 'viaje' and spl[1] == 'aproximado,':
		viaje_aproximado(grafo,spl[2])
	elif spl[0] == 'itinerario':
		intinerario(grafo,spl[2])
	elif spl[0] == 'reducir_caminos':
		reducir_caminos(grafo,spl[2])
	else:
		print('ERROR en comando' + spl[0])
	entrada = input('')








#print('\033[92m grafo\n \033[0m')
#print(grafo)
#print('\033[92m Camino minimo entre Kaliningrado y Nizhni Novgorod\n \033[0m')
#lista = camino_minimo(grafo, 'Kaliningrado', 'Nizhni Novgorod')
#print (lista)

#print('\033[92m Arbol de tendido minimo\n \033[0m')
#arbol = mst_prim(grafo, 'Moscu')
#print(arbol)

#print('\033[92m Viajante\n \033[0m')
#lista = viajante_backtracing(grafo, 'Moscu')
#print(lista)

#print('\033[92m Viajante aproximado\n \033[0m')
#lista = viajante_greedy(grafo, 'Moscu')
#print(lista)
