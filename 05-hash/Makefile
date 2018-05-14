CC = gcc
FLAGS = -g -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui

build: pruebas_catedra.c hash.c testing.c main.c
	$(CC) -g -c  -Wall -Wconversion -Wno-sign-conversion -Werror pruebas_catedra.c hash.c testing.c main.c

cpruebas: build
	$(CC) $(FLAGS) *.o -o pruebas
	./pruebas

valgrind: build
	$(VALGRIND) ./pruebas

gdb: build
	$(GDB) pruebas
