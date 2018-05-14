bool hash_guardar(hash_t *hash, const char *clave, void *dato){ //REVISAR cuando devuelvo false?
    int posicion = hash_ubicacion(hash, clave);
    if(posicion != -1){//si lo encontro
        hash->datos[posicion].dato = dato;
        hash->datos[posicion].estado = ocupado;
    } else {//sino
        int pos_inicial = posicion;
        while(hash->datos[posicion].estado != vacio){
            if(posicion == hash->tam){
                posicion = 0;
                if(pos_inicial == 0)
                  return false;
            }
            if (posicion == pos_inicial-1)
              return false;
        }
        hash->no_vacios++;
        hash->ocupados++;
        hash->datos[posicion].clave = strdup(clave); //REVISAR strdup?  tengo que crearme una copia dinamica?
        hash->datos[posicion].estado = ocupado;
    }
    if( (hash->no_vacios / hash->tam ) >= MAX_FACTOR_CARGA){
        if(hash->no_vacios / hash->ocupados >= 2){
            return hash_redimensionar(hash, hash->tam); //creo otro del mismo tamaño
        }
        return hash_redimensionar(hash, hash->tam * INDICE_AMPLIAR); //aumento el tamaño
    }
    return true;
}
