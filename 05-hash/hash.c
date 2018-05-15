#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int TAM_INICIAL = 1000;
const int INDICE_AMPLIAR = 4;
const int MAX_FACTOR_CARGA = 2;

typedef void (*hash_destruir_dato_t)(void *);
typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

typedef enum estado{
    ocupado,
    vacio,
    borrado
}estado_t;

typedef struct nodo{
    char* clave;
    void* dato;
    estado_t estado;
}nodo_t;

struct hash{
    nodo_t* datos;
    size_t tam;
    size_t no_vacios;
    size_t ocupados;
    hash_destruir_dato_t destruir_dato;
};

bool hash_guardar(hash_t *hash, const char *clave, void *dato); //firma por motivos de recursion

void nodo_inicializar(nodo_t* nodo){
    nodo->dato = NULL;
    nodo->clave = NULL;
    nodo->estado = vacio;
}

// el -std=c99 no me dejaba usar strdup, asi que me hice uno
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

//http://www.cse.yorku.ca/~oz/hash.html   djb2
size_t hashing(const char *str){
    size_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;// hash * 33 + c
    return hash;
}

/* Crea el hash <*/
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash){
        return NULL;
    }
    hash->datos = malloc(sizeof(nodo_t) * TAM_INICIAL);
    if(!hash->datos){
        return NULL;
    }

    for (int i = 0; i < TAM_INICIAL; i++){
        nodo_inicializar(&hash->datos[i]);
    }

    hash->tam = TAM_INICIAL;
    hash->no_vacios = 0;
    hash->ocupados = 0;
    hash->destruir_dato = destruir_dato;
    return hash;
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
* destruir para cada par (clave, dato).
* Pre: La estructura hash fue inicializada
* Post: La estructura hash fue destruida
*/
void hash_destruir(hash_t *hash){
    hash_destruir_dato_t destruir = hash->destruir_dato;
    for (int i = 0; i < hash->tam; i++){
        if(destruir!= NULL){
            destruir(hash->datos[i].dato);
        }
        free(hash->datos[i].clave);
    }
    free(hash->datos);
    free(hash);
}

/* Determina si clave pertenece o no al hash, y devuelve la posicion si la encuentra
* Pre: La estructura hash fue inicializada
*/
size_t hash_ubicacion(const hash_t *hash, const char *clave, bool* encontro){
    size_t posicion = hashing(clave) % (hash->tam);
    *encontro = true;
    size_t i = 0;
    while( (i < hash->tam) && (hash->datos[posicion].estado != vacio) ){
        if (strcmp(hash->datos[posicion].clave, clave) == 0){
            return posicion;
        }
        posicion++;
        if(posicion == hash->tam){
            posicion = 0;
        }
        i++;
    }
    *encontro = false;
    return -1;
}

/* Determina si clave pertenece o no al hash.
* Pre: La estructura hash fue inicializada
*/
bool hash_pertenece(const hash_t *hash, const char *clave){
    bool encontro;
    size_t posicion = hash_ubicacion(hash, clave, &encontro);
    if (encontro && hash->datos[posicion].estado == ocupado){
        return true;
    }
    return false;
}

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
* devuelve NULL.
* Pre: La estructura hash fue inicializada
*/
void *hash_obtener(const hash_t *hash, const char *clave){
    bool encontro;
    size_t posicion = hash_ubicacion(hash, clave, &encontro);
    if(encontro == false){
        return NULL;
    }
    return hash->datos[posicion].dato;
}

// Redimensiona el vector de datos del hash
bool hash_redimensionar(hash_t *hash, size_t tam_nuevo){
    nodo_t* datos_viejos = hash->datos;
    size_t tam_viejo = hash->tam;

    hash->tam = tam_nuevo;
    hash->no_vacios = 0;
    hash->ocupados = 0;

    hash->datos = malloc(sizeof(nodo_t) * tam_nuevo);
    if(!hash->datos){
        return false;
    }

    for (int i = 0; i < tam_nuevo; i++){
        nodo_inicializar(&hash->datos[i]);
    }

    for (int i = 0; i < tam_viejo; i++){
        if(datos_viejos[i].estado == ocupado){
            if (hash_guardar(hash, datos_viejos[i].clave, datos_viejos[i].dato) == false){
                return false;
            }
        }
        if(datos_viejos[i].clave != NULL){
            free(datos_viejos[i].clave);
        }
    }
    free(datos_viejos);

    return true;
}

// Devuelve la siguiente posicion que no esta ocupada
//PRE: el vector de hash nunca va a esta lleno*/
size_t buscar_desocupado(hash_t* hash,size_t inicio,size_t tope){
    size_t i = inicio + 1;
    while(hash->datos[i].estado == ocupado){
        i++;
        if(i == tope){
            i = 0;
        }
    }
    return i;
}

// En el caso de que deba redimensionar el hash, lo hace
bool vericar_tamanio(hash_t* hash){
    if(hash->ocupados * MAX_FACTOR_CARGA >= hash->tam){
        return hash_redimensionar(hash, hash->tam * INDICE_AMPLIAR);
    }
    return true;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
* estructura, la reemplaza. De no poder guardarlo devuelve false.
* Pre: La estructura hash fue inicializada
* Post: Se almacenó el par (clave, dato)
*/
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    bool encontro;
    size_t posicion = hash_ubicacion(hash, clave, &encontro);
    if(encontro){
        hash_destruir_dato_t destruir = hash->destruir_dato;
        if(destruir != NULL){
            destruir(hash->datos[posicion].dato);
        }
    }
    if(!encontro){
        posicion = hashing(clave) % (hash->tam);
        if(hash->datos[posicion].estado == ocupado){
            posicion = buscar_desocupado(hash, posicion, hash->tam);
        }
        if(hash->datos[posicion].estado == vacio){
            hash->no_vacios++;
        }
        hash->datos[posicion].clave = strdup(clave);
        if (hash->datos[posicion].clave == NULL){
            return false;
        }
    }
    if (hash->datos[posicion].estado != ocupado){
        hash->ocupados++;
    }
    hash->datos[posicion].dato = dato;
    hash->datos[posicion].estado = ocupado;
    return vericar_tamanio(hash);
}

/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve
* NULL si el dato no estaba.
* Pre: La estructura hash fue inicializada
* Post: El elemento fue borrado de la estructura y se lo devolvió,
* en el caso de que estuviera guardado.
*/
void *hash_borrar(hash_t *hash, const char *clave){
    void* dato;
    bool encontro;
    size_t posicion = hash_ubicacion(hash, clave, &encontro);
    if(!encontro || hash->datos[posicion].estado == borrado){
        return NULL;
    }
    dato = hash->datos[posicion].dato;
    hash->datos[posicion].dato = NULL;
    hash->datos[posicion].estado = borrado;
    hash->ocupados--;
    vericar_tamanio(hash);
    return dato;
}

/* Devuelve la cantidad de elementos del hash.
* Pre: La estructura hash fue inicializada
*/
size_t hash_cantidad(const hash_t *hash){
    return hash->ocupados;
}

//---------------------------------------------------------------------------//
/* Iterador del hash */

struct hash_iter{
    const hash_t* hash;
    int posicion;
};


//devuelve la siguiente posicion ocupada sin contar la posicion actual
int siguiente_ocupado(const hash_iter_t *iter){
    int i = (iter->posicion) + 1;
    while(i < iter->hash->tam &&(iter->hash->datos[i].estado != ocupado) ){
        i++;
    }
    if ( i == iter->hash->tam){
        return -1;
    }
    return i;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    if(iter->posicion == -1 ){
        return true;
    }
    return false;
}



// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter){
    if (hash_iter_al_final(iter)){
        return false;
    }
    (iter->posicion) = siguiente_ocupado(iter);
    return true;
}

// Crea iterador
hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(!iter){
        return NULL;
    }
    iter->hash = hash;
    iter->posicion = 0;
    if((hash->datos)[0].estado != ocupado){
        iter->posicion = siguiente_ocupado(iter);
    }
    return iter;
}


// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if(hash_iter_al_final(iter)){
        return NULL;
    }
    return iter->hash->datos[iter->posicion].clave;
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter){
    free(iter);
}
