bool agregar_archivo(const char* file){
    if(!file) {
        return false;
    }
    FILE* input = fopen(file,"rt");
    hash_t* hash = hash_crear(lista_destruir);
    if(!hash){
        return false;
    }

    char* buffer = NULL;
    size_t cant = 0;
    char** line;

    char* ip;
    char* fecha;
    lista_t* lista;

    while (getline(&buffer,&cant,input) > 0){
        line = split(buffer,'\t');
        ip = line[0];
        fecha = line[1];

        lista = hash_obtener(hash, ip);
        if(!lista){
            lista = lista_crear();
            lista_insertar_ultimo(lista, fecha);
            hash_guardar(hash, ip, lista);
        } else {
            lista_insertar_ultimo(lista, fecha);
        }
        free_strv(line);
    }
    free(buffer);
    fclose(input);

    hash_iter_t* hash_iter = hash_iter_crear(hash);
    if(!hash_iter){
        return false;
    }
    lista_iter_t* lista_iter_1;
    lista_iter_t* lista_iter_2;
    char* fecha_1;
    char* fecha_2;
    bool ip_actual_ataco;

    heap_t* heap = heap_crear(ipcmp_inv);
    if(!heap){
        return false;
    }

    while(!hash_iter_al_final(iter)){
        ip = hash_iter_ver_actual(iter);
        ip_actual_ataco = false;
        lista = hash_obtener(hash, ip);

        lista_iter_1 = lista_iter_crear(lista);
        lista_iter_2 = lista_iter_crear(lista);
        for (int i = 0; i < 5; i++){
            lista_iter_avanzar(lista_iter_1);
        }

        while(!lista_iter_al_final(lista_iter_1) && !ip_actual_ataco){
            if(time_diference(fecha_1; fecha_2) >= DOS_MAXIMUM_TIME){
                heap_encolar(heap, ip);
                ip_actual_ataco = true;
            }
        }

        lista_iter_destruir(lista_iter_1);
        lista_iter_destruir(lista_iter_2);

    }
    while(!heap_esta_vacio(heap)){
        printf("DoS: %s\n", (char*)heap_desencolar(heap));
    }

    hash_iter_destruir(hash_iter);
    hash_destruir(hash);

    return true;
}
