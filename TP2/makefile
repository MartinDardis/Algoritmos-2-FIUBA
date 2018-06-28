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

.PHONY: clean
clean:
	rm *.o
	rm programa
	rm *.part
