#define _POSIX_C_SOURCE 200809L
#define TAM_LINEA 200
#include "tp2.h"

#define ARCHIVO_AUXILIAR "archivo_auxiliar"
#define EXTENSION ".log"


typedef struct registro{
    char ip[20];
    char fecha[30];
    char metodo[5];
    char url[145];
}registro_t;

typedef struct registro_numerado{
    char* linea;
    size_t numero_archivo;
}registro_numerado_t;

registro_t leer_registro(const char* linea){
    char** vector = split(linea, '\t');
    registro_t registro;
    strcpy(registro.ip, vector[0]);
    strcpy(registro.fecha, vector[1]);
    strcpy(registro.metodo, vector[2]);
    strcpy(registro.url, vector[3]);
    free_strv(vector);
    return registro;
}

int comparacion_de_registro(registro_t registro_1, registro_t registro_2){
    int comparacion_fecha = strcmp(registro_1.fecha, registro_2.fecha);
    if(comparacion_fecha < 0) return 1;
    if(comparacion_fecha > 0) return -1;

    int comparacion_metodo = strcmp(registro_1.metodo, registro_2.metodo);
    int comparacion_ip = ipcmp(registro_1.ip, registro_2.ip);
    if(comparacion_ip < 0) return 1;
    if(comparacion_ip > 0) return -1;

    if(comparacion_metodo < 0) return 1;
    if(comparacion_metodo > 0) return -1;

    int comparacion_url =strcmp(registro_1.url, registro_2.url);
    if(comparacion_url < 0) return 1;
    else return -1;
}

int comparacion_de_linea(const void* linea_1, const void* linea_2){
    registro_t registro_1 = leer_registro(linea_1);
    registro_t registro_2 = leer_registro(linea_2);
    return comparacion_de_registro(registro_1, registro_2);
}

int comparacion_de_registro_numerado(const void* valor_1, const void* valor_2){
    registro_numerado_t* registro_numerado_1 = (registro_numerado_t*)valor_1;
    registro_numerado_t* registro_numerado_2 = (registro_numerado_t*)valor_2;
    return comparacion_de_linea(registro_numerado_1->linea, registro_numerado_2->linea);
}

heap_t* leer_archivo(FILE** input, size_t maximas_lineas){
    size_t contador = 0;

    heap_t* heap = heap_crear(comparacion_de_linea);

    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos;

    while((contador < maximas_lineas) && ((leidos = getline(&linea, &capacidad, *input)) > 0)){
        heap_encolar(heap, strdup(linea));
        free(linea);
        linea = NULL;
    }

    free(linea);
    return heap;
}

bool escribir_auxiliar(heap_t* heap, size_t contador_archivos_auxiliares){
    char nombre_de_auxiliar[50];
    sprintf(nombre_de_auxiliar, "%s%lu%s", ARCHIVO_AUXILIAR, contador_archivos_auxiliares, EXTENSION);
    FILE* auxiliar = fopen(nombre_de_auxiliar, "w");
    if(!auxiliar){
        return false;
    }

    while(!heap_esta_vacio(heap)){
        char* linea = heap_desencolar(heap);
        fprintf(auxiliar, "%s", linea);
        free(linea);
    }

    fclose(auxiliar);
    return true;
}

registro_numerado_t* registro_numerado_crear(char* linea, size_t numero_archivo){
    registro_numerado_t* registro_numerado = malloc(sizeof(registro_numerado_t));
    registro_numerado->linea = linea;
    registro_numerado->numero_archivo = numero_archivo;
    return registro_numerado;
}

void registro_numerado_destruir(registro_numerado_t* registro_numerado){
    free(registro_numerado->linea);
    free(registro_numerado);
}

void unir_archivos(FILE* output, size_t numero_archivos){
    heap_t* heap = heap_crear(comparacion_de_registro_numerado);
    FILE** arreglo_archivos = malloc(sizeof(FILE*)*numero_archivos);
    char nombre_de_auxiliar[50];
    size_t numero_archivo;

    char* linea = NULL;
    size_t capacidad = 0;

    for(int i = 0; i < numero_archivos; i++){
        sprintf(nombre_de_auxiliar, "%s%i%s", ARCHIVO_AUXILIAR, i, EXTENSION);
        arreglo_archivos[i] = fopen(nombre_de_auxiliar, "r");
        getline(&linea, &capacidad, arreglo_archivos[i]);
        registro_numerado_t* registro_numerado = registro_numerado_crear(linea, i);
        linea = NULL;
        capacidad = 0;
        heap_encolar(heap, registro_numerado);
    }

    while(!heap_esta_vacio(heap)){
        registro_numerado_t* registro_numerado = heap_desencolar(heap);
        numero_archivo = registro_numerado->numero_archivo;
        fprintf(output, "%s", registro_numerado->linea);
        registro_numerado_destruir(registro_numerado);

        if(!feof(arreglo_archivos[numero_archivo])){
            getline(&linea, &capacidad, arreglo_archivos[numero_archivo]);
            registro_numerado = registro_numerado_crear(linea, numero_archivo);
            linea = NULL;
            capacidad = 0;
            heap_encolar(heap, registro_numerado);
        }
    }

    heap_destruir(heap, NULL);
    for(int i = 0; i < numero_archivos; i++){
        fclose(arreglo_archivos[i]);
        sprintf(nombre_de_auxiliar, "%s%i%s", ARCHIVO_AUXILIAR, i, EXTENSION);
        remove(nombre_de_auxiliar);
    }
    free(arreglo_archivos);
}

bool ordenar_archivo(const char* input_file,const char* output_file,const size_t max_memoria){
    FILE* input = fopen(input_file, "r");
    if(!input){
        return RET_ERROR;
    }

    FILE* output = fopen(output_file, "w");
    if(!output){
        fclose(input);
        return RET_ERROR;
    }

    size_t maximas_lineas = (max_memoria * 1024) / TAM_LINEA;
    size_t contador_archivos_auxiliares = 0;
    while(!feof(input)){
        heap_t* heap = leer_archivo(&input, maximas_lineas);
        escribir_auxiliar(heap, contador_archivos_auxiliares);
        heap_destruir(heap, free);
        contador_archivos_auxiliares++;
    }
    fclose(input);

    unir_archivos(output, contador_archivos_auxiliares);
    fclose(output);
    return RET_OK;
}
