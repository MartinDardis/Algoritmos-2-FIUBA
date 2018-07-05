#define _XOPEN_SOURCE
#include "tp2.h"
#include <time.h>
#define TIME_FORMAT "%FT%T%z"

#define DOS_MAXIMUM_ACCESS 5
#define DOS_MAXIMUM_TIME 2

time_t iso8601_to_time(const char* iso8601){
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}
/************************ Primitivas internas *********************************/
void destruir(void* dato);
int ipcmp_inv(const void* a,const void* b);
hash_t* generar_hash(const char* file, abb_t** puntero_abb);
double diferencia_tiempo(const char* a,const char* b);
void imprimir_dos(void* ip);
/******************************************************************************/

//call (char*)lista_ver_primero(hash_obtener(hash, "207.255.245.133"))

bool agregar_archivo(const char* file, abb_t** puntero_abb){
    hash_t* hash = generar_hash(file, puntero_abb);
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
        //if(!lista) printf("no lista");

        lista_iter_t* lista_iter_1 = lista_iter_crear(lista);
        for (int i = 0; (i < DOS_MAXIMUM_ACCESS-1) && !lista_iter_al_final(lista_iter_1); i++){
            //printf("fecha %i: %s, %p\n", i, (char*)lista_iter_ver_actual(lista_iter_1), lista_iter_ver_actual(lista_iter_1));
            lista_iter_avanzar(lista_iter_1);
        }
        lista_iter_t* lista_iter_2 = lista_iter_crear(lista);
        while(!lista_iter_al_final(lista_iter_1) && !ip_actual_ataco){
            char* fecha_1 = (char*)lista_iter_ver_actual(lista_iter_1); //REVISAR strdup
            char* fecha_2 = (char*)lista_iter_ver_actual(lista_iter_2);
            //printf("fecha_1: %s, fecha_2: %s\n", fecha_1, fecha_2);
            if(diferencia_tiempo(fecha_1, fecha_2) < DOS_MAXIMUM_TIME){// hay q hacer conversion de string a time para usar difftime
                //printf("diferencia: %f\n", diferencia_tiempo(fecha_1, fecha_2));
                heap_encolar(heap, ip);
                ip_actual_ataco = true;
            } else {

                lista_iter_avanzar(lista_iter_1);
                fecha_1 =(char*)lista_iter_ver_actual(lista_iter_1);
                lista_iter_avanzar(lista_iter_2);
                fecha_2 = (char*)lista_iter_ver_actual(lista_iter_2);
            }
        }
        lista_iter_destruir(lista_iter_1);
        lista_iter_destruir(lista_iter_2);
        if(!ip_actual_ataco) free(ip);
        hash_iter_avanzar(hash_iter);
    }

    while(!heap_esta_vacio(heap)){
        imprimir_dos(heap_desencolar);
    }
    heap_destruir(heap, NULL);
    hash_iter_destruir(hash_iter);
    hash_destruir(hash);
    return RET_OK;
}

void destruir(void* dato){
    if(dato){
        lista_destruir((lista_t*)dato,free);
    }
}

int ipcmp_inv(const void* a,const void* b){
  return ((-1) * ipcmp((char*)a,(char*)b));
}

hash_t* generar_hash(const char* file, abb_t** puntero_abb){ //REVISAR nombre
    FILE* input = fopen(file,"rt");
    if(!input){
        return NULL;
    }

    hash_t* hash = hash_crear(destruir);
    if(!hash){
        return NULL;
    }
    char* buffer = NULL;
    size_t cant = 0;
    while (!feof(input) && getline(&buffer,&cant,input) > 0){
        char ip[30];
        char* fecha = malloc(sizeof(char)*26);
        char** line = split(buffer,'\t');
        strcpy(ip,line[0]);
        strcpy(fecha,line[1]);
        lista_t* lista = hash_obtener(hash, ip);
        if(!lista){
            lista = lista_crear();
            lista_insertar_ultimo(lista, fecha);
            //printf("fecha guardada %s, %p\n", (char*)lista_ver_ultimo(lista), lista_ver_ultimo(lista));
            hash_guardar(hash, ip, lista);
            abb_guardar(*puntero_abb, ip, NULL); //REVISAR O(log n)
        } else {
            lista_insertar_ultimo(lista, fecha);
            //printf("fecha guardada %s, %p\n", (char*)lista_ver_ultimo(lista), lista_ver_ultimo(lista));
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
