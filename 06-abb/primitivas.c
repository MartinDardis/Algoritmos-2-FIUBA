typedef struct nodo{
    char* clave;
    void* dato;
    nodo_t* hijo_izq;
    nodo_t* hijo_der;
} nodo_t;

typedef struct abb{
    nodo_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
} abb_t;

/*    Declaracion de Primitivas para funciones internas del abb                          */
bool remplazar_dato(abb_comparar_clave_t* cmp,nodo_t* padre,const char* clave,void* dato);
bool insertar_dato(abb_comparar_clave_t* cmp,nodo_t* padre,const char* clave,void* dato);
void* buscar_y_borrar(abb_comparar_clave_t* cmp,nodo_t* padre,const char* clave);
/*****************************************************************************************/

nodo_t* crear_nodo(const char* clave,void* dato){
  nodo_t* nuevo = malloc(sizeof(nodo_t));
  if(!nuevo) return NULL;
  nuevo->clave = strdup(clave);
  nuevo->dato = dato;
  nuevo->hijo_izq = NULL;
  nuevo->hijo_der = NULL;
  return nuevo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* nuevo = malloc(sizeof(abb_t));
  nuevo->raiz = NULL;
  nuevo->cmp = cmp;
  nuevo->destruir_dato = destruir_dato;
  nuevo->cant = 0;
  return nuevo;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  bool guardo = true;
  if (arbol == NULL)
    guardo = false;
  else if(arbol->raiz == NULL){
    arbol->raiz = crear_nodo(clave,dato);
    if(!arbol->raiz)
      guardo = false;
  }
  else if ( abb_pertenece(arbol,clave) )
    guardo = remplazar_dato(arbol->cmp,arbol->raiz,clave,dato);
  else
    guardo = insertar_dato(arbol->raiz,clave,dato);
  return guardo;
}

bool remplazar_dato(abb_comparar_clave_t* cmp,nodo_t* padre,const char* clave,void* dato){
  int comparacion = cmp(padre->clave,clave)
  if(comparacion == 0){
    padre->dato = dato;
    return true;
  }
  else if (comparacion < 0)
    return remplazar_dato(cmp,padre->hijo_izq,clave,dato);
  else
    return remplazar_dato(cmp,padre->hijo_der,clave,dato);
}
bool insertar_dato(abb_comparar_clave_t* cmp,nodo_t* padre,const char* clave,void* dato){
  int comparacion = cmp(padre->clave,clave)
  if ( comparacion < 0 && hijo->izq != NULL)
    insertar_dato(cmp,padre->hijo_izq,clave,dato);
  else if (comparacion > 0 && hijo->der != NULL)
    insertar_dato(cmp,padre->hijo_der,clave,dato);
  else{
    nodo_t* nuevo = crear_nodo(clave,dato);
    if(!nuevo) return false;
    if (comparacion < 0){
      padre->hijo_izq = nuevo;
    else
      padre->hijo_der = nuevo;
  }
  return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){
  if (!arbol) return NULL;
  if(!abb_pertenece(arbol,clave)) return NULL;
  return buscar_y_borrar(arbol->cmp,arbol->raiz,clave);
}
