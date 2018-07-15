
def procesar_linea(linea):
    linea = linea.split(',')
    param_2 = linea [1]
    param_2 = param_2.rstrip()
    param_2 = param_2[1:]
    linea = linea[0].split(' ')
    if len(linea) == 2:
        comando = linea[0]
        param_1 = linea[1]
    else:
        sep = ' '
        comando = sep.join(linea[0],linea[1])
        param_1 = linea [2]
    return comando,param_1,param_2

print('ir moscu, restov del don')
print(procesar_linea('ir moscu, restov del don'))
