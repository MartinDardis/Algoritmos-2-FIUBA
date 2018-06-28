#define _XOPEN_SOURCE
#include "tp2.h"
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
void imprimir_dos(void* ip);
/******************************************************************************/

bool agregar_archivo(const char* file){
    hash_t* hash = generar_hash(file);
    if(!hash){
        return RET_ERROR;
    }
    hash_iter_t* hash_iter = hash_iter_crear(hash);
    if(!hash_iter){
        return RET_ERROR;
    }
    bool ip_actual_ataco;
    heap_t* heap = heap_crear(ipcmp_inv);
    if(!heap){
        return RET_ERROR;
    }
    while(!hash_iter_al_final(hash_iter)){
        char* ip = strdup(hash_iter_ver_actual(hash_iter));
        ip_actual_ataco = false;
        lista_t* lista = hash_obtener(hash, ip);

        lista_iter_1 = lista_iter_crear(lista);
        for (int i = 0; i < 5; i++){
            lista_iter_avanzar(lista_iter_1);
        }
        fecha_1 = lista_iter_ver_actual(lista_iter_1);
        lista_iter_2 = lista_iter_crear(lista);
        fecha_2 = lista_iter_ver_actual(lista_iter_2);

        while(!lista_iter_al_final(lista_iter_1) && !ip_actual_ataco){
            char* fecha_1 = strdup((char*)lista_iter_ver_actual(lista_iter_1));
            char* fecha_2 = strdup((char*)lista_iter_ver_actual(lista_iter_2));
            if(diferencia_tiempo(fecha_1, fecha_2) >= DOS_MAXIMUM_TIME){// hay q hacer conversion de string a time para usar difftime
                heap_encolar(heap, ip);
                ip_actual_ataco = true;
            } else {
                lista_iter_avanzar(lista_iter_1);
                fecha_1 = lista_iter_ver_actual(lista_iter_1);
                lista_iter_avanzar(lista_iter_2);
                fecha_2 = lista_iter_ver_actual(lista_iter_2);
            }
            free(fecha_1);
            free(fecha_2);
        }
        lista_iter_destruir(lista_iter_1);
        lista_iter_destruir(lista_iter_2);
        if(!ip_actual_ataco) free(ip);
    }
    heap_destruir(heap,imprimir_dos);
    hash_iter_destruir(hash_iter);
    hash_destruir(hash);
    return RET_OK;
}

void destruir(void* dato){
  lista_destruir(dato,NULL);
}
int ipcmp_inv(const void* a,const void* b){
  return (0 - ipcmp((char*)a,(char*)b));
}
hash_t* generar_hash(const char* file){
    FILE* input = fopen(file,"rt");
    if(!input)
      return NULL;
    hash_t* hash = hash_crear(destruir);
    if(!hash){
        return NULL;
    }
    char* buffer = NULL;
    size_t cant = 0;
    while (!feof(input) && getline(&buffer,&cant,input) > 0){
        char ip[30];
        char fecha[50];
        char** line = split(buffer,'\t');
        strcpy(ip,line[0]);
        strcpy(fecha,line[1]);
        lista_t* lista = hash_obtener(hash, ip);
        if(!lista){
            lista = lista_crear();
            lista_insertar_ultimo(lista, fecha);
            hash_guardar(hash, ip, lista);
        } else {
            lista_insertar_ultimo(lista, fecha);

        }
        free_strv(line);
        free(buffer);
        buffer = NULL;
        cant = 0;
    }
    free(buffer);
    fclose(input);
    return hash;
}

double diferencia_tiempo(const char* a,const char* b){
  double diff = difftime(iso8601_to_time(a),iso8601_to_time(b));
  return diff;
}

void imprimir_dos(void* ip){
  printf("DoS: %s\n",(char*) ip);
  free(ip);
}
