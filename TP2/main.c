#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tp2.h"


/**************************** CONSTANTES *************************************/
#define ORDENAR "ordenar_archivo"
#define AGREGAR "agregar_archivo"
#define VER "ver_visitantes"
#define ERROR -1
#define CANT_PARAM_INCORRECTO "Cantidad de parametros invalida"
#define PARAM_INVALIDO "Parametro Incorrecto"
/**************************** FUNCIONES INTERNAS ******************************/
size_t analizar_comando(char** command);
void print_result(bool state,char* command);
/*****************************************************************************/

int main (int argc,char* argv[]){
    if(argc != 2){
        fprintf(stderr, "%s\n",CANT_PARAM_INCORRECTO);
        return ERROR;
    }

    const int max_memory = atoi(argv[1]);
    if(max_memory == 0){
        fprintf(stderr, "%s\n",PARAM_INVALIDO);
        return ERROR;
    }

    abb_t* abb = abb_crear(ipcmp, NULL);
    if(!abb){
        return ERROR;
    }

    char* last_file = NULL;
    bool error_command = false;
    char* buffer = NULL;
    size_t size = 0;
    while(!error_command && getline(&buffer,&size,stdin)>0 ){
        char** command = split(buffer,' ');
        switch (analizar_comando(command)){
            case 1:
                last_file = strndup(command[2], strlen(command[2])-1);
                error_command = ordenar_archivo(command[1],last_file,max_memory);
                break;
            case 2:
                last_file = strndup(command[1], strlen(command[1])-1);
                error_command = agregar_archivo(last_file, &abb);
                break;
            case 3:
                error_command = ver_visitantes(abb,command[1],command[2]);
                break;
            default:
                error_command = true;
                break;
        }
        if(last_file){
            free(last_file);
            last_file = NULL;
        }
        print_result(error_command,command[0]);
        free_strv(command);
        free(buffer);
        buffer = NULL;
        size = 0;
    }
    free(buffer);
    abb_destruir(abb);
    return 0;
}

size_t analizar_comando(char** command){
    size_t selec = 0;
    size_t contador_parametros = 0;
    while(command[contador_parametros]){
        contador_parametros++;
    }
    if( strcmp(command[0],ORDENAR) == 0){
        if(contador_parametros == 3){
            selec = 1;
        } else {
            selec = 4;
        }
    }
    else if (strcmp(command[0],AGREGAR) == 0){
        if(contador_parametros == 2){
            selec = 2;
        } else {
            selec = 4;
        }
    }
    else if (strcmp(command[0],VER) == 0){
        if(contador_parametros == 3){
            selec = 3;
        } else {
            selec = 4;
        }
    }
    return selec;
}

void print_result(bool state,char* command){
    if (state){
        if(strcmp(command,"ver_visitantes\n") == 0)
          fprintf(stderr, "Error en comando %s",command);
        else
          fprintf(stderr, "Error en comando %s\n",command);
    } else {
        fprintf(stdout,"OK\n");
    }
}
