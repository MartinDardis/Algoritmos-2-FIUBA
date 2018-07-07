#include "tp2.h"

bool input_verify(const char* input);
bool print_ip(const char * clave, void * dato, void * extra);

bool ver_visitantes(abb_t* abb, const char* desde, const char* hasta){
    if(!abb || !desde || !hasta){
      return RET_ERROR;
    }
    if(input_verify(desde) || input_verify(hasta))
      return RET_ERROR;
    printf("Visitantes:\n");
    abb_in_order_desde_hasta(abb, print_ip, NULL, desde, hasta);
    return RET_OK;
}

bool print_ip(const char * clave, void * dato, void * extra){
    printf("\t%s\n",clave);
    return true;
}

bool input_verify(const char* input){
  char** input_split = split(input,'.');
  bool error = false;
  for(int i=0; i < 4 && !error ; i++){
    if(atoi(input_split[i])<0 || atoi(input_split[i])>999 )
      error = true;
  }
  if(input_split[4])
    error = true;
  return error;
}
