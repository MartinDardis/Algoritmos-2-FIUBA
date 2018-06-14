#ifndef TP2_H
#define TP2_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <heap.h>
#include "abb.h"
#include "hash.h"
#include "strutil.h"

//La funcion ordena cronologicamente un archivo log.
//recibe por parametro el nombre de un archivo de log, el nombre del archivo de salida y la cantidad
//de memoria que podra utilizar. Devuelve TRUE si pudo ordenar y False si hubo un error.
//LA CANTIDAD DE MEMORIA DEBE SER EN BYTES
bool ordenar_archivo(const char input_file[],const char out_file[],const size_t max_memory);


#endif
