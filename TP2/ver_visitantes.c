#include "tp2.h"



bool print_ip(const char * clave, void * dato, void * extra){
    printf("\t%s\n",clave);
    return true;
}

bool ver_visitantes(const char* input_file,const char* desde, const char* hasta){
    FILE* input = fopen(input_file,"rt");
    if(!input){
      return RET_ERROR;
    }
    if(!desde || !hasta){
        return RET_ERROR;
    }
    abb_t* abb = abb_crear(ipcmp, NULL);
    if(!abb){
        return RET_ERROR;
    }
    char* buffer = NULL;
    size_t cant = 0;
    char** line;

    char* ip;

    while (getline(&buffer,&cant,input) > 0){
        line = split(buffer,'\t');
        ip = line[0];
        abb_guardar(abb, ip, NULL);
    }
    free_strv(line);
    free(buffer);
    printf("Visitantes:\n");
    abb_in_order_desde_hasta(abb, print_ip, NULL, desde, hasta);
    abb_destruir(abb);
    return RET_OK;
}
