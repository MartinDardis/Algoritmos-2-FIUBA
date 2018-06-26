#ifndef TP2_H
#define TP2_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "abb.h"
#include "hash.h"
#include "lista.h"
#include "pila.h"
#include "strutil.h"

//La funcion ordena cronologicamente un archivo log.
//recibe por parametro el nombre de un archivo de log, el nombre del archivo de salida y la cantidad
//de memoria que podra utilizar. Devuelve TRUE si pudo ordenar y False si hubo un error.
//LA CANTIDAD DE MEMORIA DEBE SER EN KBYTES
bool ordenar_archivo(const char input_file[],const char out_file[],const size_t max_memory);

bool agregar_archivo(const char* file);

bool ver_visitantes(const char* input_file,const char* desde,const char* hasta);

//FUNCION DE COMPARACION DE IP, devuelve >0 si S1 > S2; 0 si S1==S2, <0 si S1<S2
int ipcmp(const char* s1,const char* s2);

#endif
