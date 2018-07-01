#include "tp2.h"

bool print_ip(const char * clave, void * dato, void * extra){
    printf("\t%s\n",clave);
    return true;
}

bool ver_visitantes(abb_t* abb, const char* desde, const char* hasta){
    if(!abb || !desde || !hasta){
      return RET_ERROR;
    }

    printf("Visitantes:\n");
    abb_in_order_desde_hasta(abb, print_ip, NULL, desde, hasta);
    return RET_OK;
}
