from sys import argv

import grafo


city_file = argv[1]
map_file = argv[2]


with open(city_file,'r') as cities:
	mode = 0
	for lines in cities:
		print (lines)
		if lines.isnumeric():
			mode = mode + 1
		elif mode == 1:
			grafo.agregar_vertice(lines)
		elif mode == 2:
			data = lines.split(',')
			grafo.agregar_arista(data[0],data[1],data[2])

print('OK')
