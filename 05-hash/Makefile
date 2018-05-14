cpruebas: pruebas_catedra.c hash.c testing.c main.c
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas pruebas_catedra.c hash.c testing.c main.c 
build: pruebas_catedra.c hash.c testing.c
	gcc -g -c  -Wall -Wconversion -Wno-sign-conversion -Werror pruebas_catedra.c hash.c testing.c
valgrind: compilarpruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
