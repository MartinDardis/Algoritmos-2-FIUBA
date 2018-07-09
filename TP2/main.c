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

#define ARGC 2
#define MEM_ARG 1

#define COMM 0
#define PARAM_1 1
#define PARAM_2 2
#define COM_SORT 1
#define COM_ADD 2
#define COM_VIEW 3
#define COM_ERR 0
/**************************** FUNCIONES INTERNAS ******************************/
size_t analizar_comando(char** command);
void print_result(bool state,char* command);
/*****************************************************************************/

int main (int argc,char* argv[]){
    if(argc != ARGC){
        fprintf(stderr, "%s\n",CANT_PARAM_INCORRECTO);
        return ERROR;
    }

    const int max_memory = atoi(argv[MEM_ARG]);
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
        switch (analizar_comando(command[COMM])){
            case 1:
                last_file = strndup(command[PARAM_2], strlen(command[PARAM_2])-1);
                error_command = ordenar_archivo(command[PARAM_1],last_file,max_memory);
                break;
            case 2:
                last_file = strndup(command[PARAM_1], strlen(command[PARAM_1])-1);
                error_command = agregar_archivo(last_file, &abb);
                break;
            case 3:
                error_command = ver_visitantes(abb,command[PARAM_1],command[PARAM_2]);
                break;
            default:
                error_command = true;
                break;
        }
        if(last_file){
            free(last_file);
            last_file = NULL;
        }
        print_result(error_command,command[COMM]);
        free_strv(command);
        free(buffer);
        buffer = NULL;
        size = 0;
    }
    free(buffer);
    abb_destruir(abb);
    return 0;
}

size_t analizar_comando(char* command){
    size_t selec = COM_ERR;
    if( strcmp(command,ORDENAR) == 0)
            selec = COM_SORT;
    else if (strcmp(command,AGREGAR) == 0)
            selec = COM_ADD;
    else if (strcmp(command,VER) == 0)
            selec = COM_VIEW;
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
