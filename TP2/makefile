CC = gcc
FLAGS_COMPILE = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LIBRARY = hash.c heap.c abb.c strutil.c pila.c lista.c
MAIN = main.c
SORT_FILE = tp2.c
ADD_FILE = agregar_archivo.c
VIEW_VISIT = ver_visitantes.c
OBJ =  hash.o heap.o abb.o strutil.o pila.o lista.o main.o tp2.o agregar_archivo.o ver_visitantes.o

build_lib:
	$(CC) -c $(FLAGS_COMPILE) $(LIBRARY)

all: $(OBJ)
	$(CC) $(FLAGS_COMPILE) *.o -o programa

%.o: %.c
	$(CC) $(FLAGS_COMPILE) -c  $< >$@

prueba: programa
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/prueba3.txt | ./programa 200

pruebas: programa
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/prueba1.txt | ./programa 200
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/prueba2.txt | ./programa 200
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/prueba3.txt | ./programa 200
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/pruebavol.txt | ./programa 200

pruebavol: programa
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes cat pruebas/pruebavol.txt | ./programa 200


gdb: programa
	gdb -tui ./programa
	cat gdb.txt

zip:
	zip "entrega.zip" *.c *.h deps.mk

.PHONY: clean
clean:
	rm *.o
	rm programa
	rm *.part
