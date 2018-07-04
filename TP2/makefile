CC = gcc
FLAGS_COMPILE = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LIBRARY = hash.c heap.c abb.c strutil.c pila.c lista.c main.c tp2.c agregar_archivo.c ver_visitantes.c ordenar_archivo.c
OBJ =  hash.o heap.o abb.o strutil.o pila.o lista.o main.o tp2.o agregar_archivo.o ver_visitantes.o

build_lib:
	$(CC) -c $(FLAGS_COMPILE) $(LIBRARY)

all: $(LIBRARY)
	$(CC) $(FLAGS_COMPILE) *.c -o programa

prueba: programa
	cat pruebas/prueba1.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes  ./programa 1
	./diff logs/access003.log logs/access011_ord.log 

pruebas: programa
	cat pruebas/prueba1.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./programa 200
	cat pruebas/prueba2.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./programa 200
	cat pruebas/prueba3.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./programa 200
	cat pruebas/pruebavol.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./programa 200


pruebavol: programa
	 cat pruebas/pruebavol.txt | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./programa 1000


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
