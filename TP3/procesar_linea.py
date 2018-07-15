def procesar_linea(linea):
    linea = linea.split(',')
    sep = ' '
    param_1 = None
    param_2 = linea [1]
    param_2 = param_2.rstrip()
    param_2 = param_2[1:]
    linea = linea[0].split(' ')
    if len(linea) == 2:
        comando = linea[0]
        param_1 = linea[1]
    elif linea[0] == 'viaje':
        sep = ' '
        comando = sep.join(linea[0],linea[1])
        for i in range(2,len(linea)):
            param_1 += linea [i]
    else:
        for i in range(2,len(linea)):
            param_1 += linea [i]
    return comando,param_1,param_2

print('ir moscu, restov del don')
print(procesar_linea('ir moscu, restov del don'))
