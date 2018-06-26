#include "tp2.h"
#define _XOPEN_SOURCE
#include <time.h>

#define TIME_FORMAT "%FT%T%z"
#define DOS_MAXIMUM_TIME 5

time_t iso8601_to_time(const char* iso8601){
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}
/************************ Primitivas internas *********************************/
void destruir(void* dato);
int ipcmp_inv(const void* a,const void* b);
hash_t* generar_hash(const char* file);
double diferencia_tiempo(const char* a,const char* b);
/******************************************************************************/

bool agregar_archivo(const char* file){
    hash_t* hash = generar_hash(file);
    if(!hash){
        return false;
    }
    hash_iter_t* hash_iter = hash_iter_crear(hash);
    if(!hash_iter){
        return false;
    }

    char* ip;
    lista_iter_t* lista_iter_1;
    lista_iter_t* lista_iter_2;
    char* fecha_1;
    char* fecha_2;
    bool ip_actual_ataco;

    heap_t* heap = heap_crear(ipcmp_inv);
    if(!heap){
        return false;
    }

    while(!hash_iter_al_final(hash_iter)){
        ip = strdup(hash_iter_ver_actual(hash_iter));
        ip_actual_ataco = false;
        lista_t* lista = hash_obtener(hash, ip);

        lista_iter_1 = lista_iter_crear(lista);
        lista_iter_2 = lista_iter_crear(lista);
        for (int i = 0; i < 5; i++){
            lista_iter_avanzar(lista_iter_1);
        }

        while(!lista_iter_al_final(lista_iter_1) && !ip_actual_ataco){
            if(diferencia_tiempo(fecha_1, fecha_2) >= DOS_MAXIMUM_TIME){// hay q hacer conversion de string a time para usar difftime
                heap_encolar(heap, ip);
                ip_actual_ataco = true;
            } else {
                lista_iter_avanzar(lista_iter_1);
                lista_iter_avanzar(lista_iter_2);
            }
        }

        lista_iter_destruir(lista_iter_1);
        lista_iter_destruir(lista_iter_2);
        free(ip);

    }
    while(!heap_esta_vacio(heap)){
        printf("DoS: %s\n", (char*)heap_desencolar(heap));
    }

    hash_iter_destruir(hash_iter);
    hash_destruir(hash);

    return true;
}


void destruir(void* dato){
  lista_destruir(dato,NULL);
}
int ipcmp_inv(const void* a,const void* b){
  return (0 - ipcmp((char*)a,(char*)b));
}
hash_t* generar_hash(const char* file){
    if(!file) {
        return NULL;
    }
    FILE* input = fopen(file,"rt");
    hash_t* hash = hash_crear(destruir);
    if(!hash){
        return NULL;
    }

    char* buffer = NULL;
    size_t cant = 0;
    char** line;

    char* ip;
    char* fecha;
    lista_t* lista;

    while (getline(&buffer,&cant,input) > 0){
        line = split(buffer,'\t');
        ip = line[0];
        fecha = line[1];

        lista = hash_obtener(hash, ip);
        if(!lista){
            lista = lista_crear();
            lista_insertar_ultimo(lista, fecha);
            hash_guardar(hash, ip, lista);
        } else {
            lista_insertar_ultimo(lista, fecha);
        }
        free_strv(line);
    }
    free(buffer);
    fclose(input);
    return hash;
}
double diferencia_tiempo(const char* a,const char* b){
  return difftime(iso8601_to_time(a),iso8601_to_time(b));
}
