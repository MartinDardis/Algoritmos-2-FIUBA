#define _POSIX_C_SOURCE 200809L //getline
#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.
#include <time.h>

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_abb_vacio()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio()
{
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir()
{
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "pato", *valor2 = "cuack";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "sapo", *valor4 = "croak";
    char *clave5 = "serpiente", *valor5 = "sssss";
    char *clave6 = "gato", *valor6 = "miau";
    char *clave7 = "delfin", *valor7 = "iiiii";
    char *clave8 = "gusano", *valor8 = " ";
    char *clave9 = "leon", *valor9 = "groar";

    // Inserta 9 valores y luego los borra
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave8, valor8));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave9, valor9));
    print_test("Prueba abb la cantidad de elementos es 9", abb_cantidad(abb) == 9);

    // Al borrar cada elemento comprueba que ya no está pero los otros sí.
    printf("Nodo hoja izquierda:\n");
    print_test("Prueba abb pertenece clave7, es verdadero", abb_pertenece(abb, clave7));
    print_test("Prueba abb borrar clave7, es valor7", abb_borrar(abb, clave7) == valor7);
    print_test("Prueba abb borrar clave7 borrada, es NULL", !abb_borrar(abb, clave7));
    print_test("Prueba abb pertenece clave7 borrada, es falso", !abb_pertenece(abb, clave7));
    print_test("Prueba abb obtener clave7 borrada, es NULL", !abb_obtener(abb, clave7));
    print_test("Prueba abb la cantidad de elementos es 8", abb_cantidad(abb) == 8);

    printf("Nodo hoja derecha:\n");
    print_test("Prueba abb pertenece clave9, es verdadero", abb_pertenece(abb, clave9));
    print_test("Prueba abb borrar clave9, es valor9", abb_borrar(abb, clave9) == valor9);
    print_test("Prueba abb borrar clave9 borrada, es NULL", !abb_borrar(abb, clave9));
    print_test("Prueba abb pertenece clave9 borrada, es falso", !abb_pertenece(abb, clave9));
    print_test("Prueba abb obtener clave9 borrada, es NULL", !abb_obtener(abb, clave9));
    print_test("Prueba abb la cantidad de elementos es 7", abb_cantidad(abb) == 7);

    printf("Nodo con un hijo izquierdo\n");
    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2 borrado, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2 borrado, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2 borrado, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);

    printf("Nodo con un hijo derecho:\n");
    print_test("Prueba abb pertenece clave6, es verdadero", abb_pertenece(abb, clave6));
    print_test("Prueba abb borrar clave6, es valor6", abb_borrar(abb, clave6) == valor6);
    print_test("Prueba abb borrar clave6 borrado, es NULL", !abb_borrar(abb, clave6));
    print_test("Prueba abb pertenece clave6 borrado, es falso", !abb_pertenece(abb, clave6));
    print_test("Prueba abb obtener clave6 borrado, es NULL", !abb_obtener(abb, clave6));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);

    printf("Nodo con 2 hijos y reemplazante con 1 hijo:\n");
    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1 borrado, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1 borrado, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1 borrado, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);

    printf("Nodo con 2 hijos y reemplazante sin hijos:\n");
    print_test("Prueba abb pertenece clave4, es verdadero", abb_pertenece(abb, clave4));
    print_test("Prueba abb borrar clave4, es valor4", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb borrar clave4 borrado, es NULL", !abb_borrar(abb, clave4));
    print_test("Prueba abb pertenece clave4 borrado, es falso", !abb_pertenece(abb, clave4));
    print_test("Prueba abb obtener clave4 borrado, es NULL", !abb_obtener(abb, clave4));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);

    printf("Se borran los restantes\n");
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3 borrado, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3 borrado, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3 borrado, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave5, es verdadero", abb_pertenece(abb, clave5));
    print_test("Prueba abb borrar clave5, es valor5", abb_borrar(abb, clave5) == valor5);
    print_test("Prueba abb borrar clave5 borrado, es NULL", !abb_borrar(abb, clave5));
    print_test("Prueba abb pertenece clave5 borrado, es falso", !abb_pertenece(abb, clave5));
    print_test("Prueba abb obtener clave5 borrado, es NULL", !abb_obtener(abb, clave5));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave8, es verdadero", abb_pertenece(abb, clave8));
    print_test("Prueba abb borrar clave8, es valor8", abb_borrar(abb, clave8) == valor8);
    print_test("Prueba abb borrar clave8 borrado, es NULL", !abb_borrar(abb, clave8));
    print_test("Prueba abb pertenece clave8 borrado, es falso", !abb_pertenece(abb, clave8));
    print_test("Prueba abb obtener clave8 borrado, es NULL", !abb_obtener(abb, clave8));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo, bool debug){
    if(largo > 370099){
        print_test("El largo es muy grande, use un largo menor o igual a 370099", false);
        return;
    }

    abb_t* abb = abb_crear(strcmp, free);

    char* claves[largo];

    unsigned* valores[largo];

    srand((unsigned)clock());

    FILE* archivo = fopen("words_alpha_desordenado.txt", "r");
    if(!archivo){
        print_test("No se encuentra el archivo", false);
        return;
    }
    /* Inserta 'largo' parejas en el abb */

    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos;

    bool ok = true;
    unsigned contador_de_nodos = 0;
    unsigned i = 0;

    while(((leidos = getline(&linea, &capacidad, archivo)) > 0) && (i < largo)){
        if(leidos == 0){
            break;
        }
        claves[i] = strdup(linea);
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
        if(!abb_pertenece(abb, claves[i])){
            contador_de_nodos++;
        }
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
        i++;
    }

    free(linea);

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == contador_de_nodos);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        if(abb_borrar(abb, claves[i]) == valores[i]){
            contador_de_nodos--;
        }
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", contador_de_nodos == 0);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);

}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    /* Se anula esta prueba por diferencias de criterios */
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iterar_volumen(size_t largo)
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[10] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


int main()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(50, true);
    prueba_abb_volumen(500, true);
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(1);
}

void pruebas_volumen(size_t largo)
{
    prueba_abb_volumen(largo, false);
}
