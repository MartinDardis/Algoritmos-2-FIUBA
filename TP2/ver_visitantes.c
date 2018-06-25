#include "tp2.h"

bool print_ip(const char * clave, void * dato, void * extra){
    printf("%s",clave);
    return true;
}

bool ver_visitantes(const char* input_file,const char* desde, const char* hasta){
    printf("1\n");
    if(!input_file || !desde || !hasta){
        return false;
    }
    FILE* input = fopen(input_file,"r");
    if(!input){
        return false;
    }
    printf("2\n");
    abb_t* abb = abb_crear(ipcmp, NULL);
    if(!abb){
        return false;
    }
    printf("se creo\n");
    char* buffer = NULL;
    size_t cant = 0;
    char** line;

    char* ip;

    while (!feof(input) && getline(&buffer,&cant,input) > 0){
        line = split(buffer,'\t');
        ip = line[0];
        abb_guardar(abb, ip, NULL);
    }
    free_strv(line);
    free(buffer);

    abb_in_order_desde_hasta(abb, print_ip, NULL, desde, hasta);
    abb_destruir(abb);
    return true;
}
