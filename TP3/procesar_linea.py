def separar(entrada):
    split = entrada.split(' ')
    if split [0] == 'viaje':
        comando = split[0]+' '+split[1]
        param_1=''
        for i in range(2,len(split)):
                param_1 +=split[i]
                if not i == len(split):
                    param_1 += ' '
        param_1 = param_1.rstrip()
        comando = comando[:-1]
        return comando , param_1
    elif split [0] == 'ir':
        param_1 =''
        param_2 =''
        ultimo = 1
        for i in range(1,len(split)):
            ultimo = i
            param_1 += split[i]
            if ',' in split[i]:
                break
            else:
                param_1 += ' '
        for i in range(ultimo+1,len(split)):
            param_2 += split[i]
            param_2 += ' '
        param_1 = param_1[:-1]
        param_2 = param_2[:-1]
        return split[0],param_1,param_2
    else:
        return split[0],split[1]

print('ir moscu, restov del don')
print(separar('ir moscu, restov del don'))
print(separar('ir restov del don, restov del don'))
print(separar('viaje optimo, moscu'))
print(separar('itinerario Moscu'))
print(separar('reducir_caminos mapa.csv'))
