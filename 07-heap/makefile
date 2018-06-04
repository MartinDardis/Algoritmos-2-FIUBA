CC = gcc
FLAGS = -g -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui
ARCHIVOS = pruebas_alumno.c heap.c testing.c main.c

build: $(ARCHIVOS)
	$(CC) -c $(FLAGS) $(ARCHIVOS)

execute: build
	$(CC) $(FLAGS) *.o -o pruebas
	./pruebas

valgrind: build
	$(VALGRIND) ./pruebas

gdb: build
	$(GDB) pruebas
