#define _POSIX_C_SOURCE 200809L

#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"




/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/


int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_heap_alumno();

    return failure_count() > 0;
}
