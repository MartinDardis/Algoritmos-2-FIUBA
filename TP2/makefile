CC = gcc
FLAGS_COMPILE = -g -c
LIBRARY = hash.c heap.c abb.c strutil.c pila.c lista.c
MAIN = main.c
SORT_FILE = tp2.c
ADD_FILE = agregar_archivo.c
VIEW_VISIT = ver_visitantes.c

build_lib:
	$(CC) $(FLAGS_COMPILE) $(LIBRARY)

build_sort: $(SORT_FILE) build_lib
	$(CC) $(FLAGS_COMPILE) $(SORT_FILE)

build_add: $(ADD_FILE) build_lib
	$(CC) $(FLAGS_COMPILE) $(ADD_FILE)

build_view: $(VIEW_VISIT) build_lib
	$(CC) $(FLAGS_COMPILE) $(VIEW_VISIT)

all: build_lib build_sort build_add build_view
	$(CC) $(MAIN) -o programa


clear:
	rm *.o
	rm *.part
	rm programa
