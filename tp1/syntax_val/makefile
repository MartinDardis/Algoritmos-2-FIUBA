CC = gcc
FLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui

build: syntax_c.c pila.c pila.h
	$(CC) $(FLAGS) -c syntax_c.c pila.c
execute: build
	$(CC) *.o -o syntax

valgrind: build
	$(VALGRIND) ./syntax

clear:
	rm -f *.o
	rm syntax
