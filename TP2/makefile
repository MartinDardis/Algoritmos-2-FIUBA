CC = gcc
FLAGS_COMPILE = -g -c
LIBRARY = hash.c heap.c abb.c strutil.c pila.c lista.c
MAIN = main.c
SORT_FILE = tp2.c
ADD_FILE = agregar_archivo.c
VIEW_VISIT = ver_visitantes.c

build_lib:
	$(CC) $(FLAGS_COMPILE) $(LIBRARY)

build_sort: $(SORT_FILE)
	$(CC) heap.o strutil.o $(MAIN) $(SORT_FILE) -o sort

clear:
	rm sort
	rm *.o
	rm *.part
