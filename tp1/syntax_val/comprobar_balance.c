bool comprobar_balance (lista_t* caracteres){
  bool balanceado = true;
  while ( !lista_esta_vacia (caracteres) && balanceado == true ){
    switch ( *((char*)lista_ver_primero(caracteres)) ) {
      case PARENTESIS_ABIERTO:
        balanceado = buscar_pareja(PARENTESIS_CERRADO,caracteres);
        break;
      case CORCHETE_ABIERTO:
        balanceado = buscar_pareja(CORCHETE_CERRADO,caracteres);
        break;
      case LLAVE_ABIERTA:
        balanceado = buscar_pareja(LLAVE_CERRADA,caracteres);
        break;
      default:
        balanceado = false;
        break;
      }
  }
  return balanceado;
}

bool buscar_pareja(char caracter , lista_t* lista){
  bool encontro = false;
  lista_iter_t* iterador = lista_iter_crear(lista);
  lista_iter_avanzar(iterador);//Me posc. en el segundo elemento
  if ( *((char*)lista_iter_ver_actual(lista)) == caracter) //Miro el siguiente
    eliminar_secuencial(lista);
    encontro = true;
  }
  else if ( *((char*)lista_ver_ultimo(lista)) == caracter){//miro el ultimo
    eliminar_anidado(lista);
    encontro = true;
  }
  lista_iter_destruir(iterador);
  return encontro;
}
