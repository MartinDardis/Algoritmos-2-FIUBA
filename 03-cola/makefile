CC = gcc
FLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui

build: *.c *.h
	$(CC) $(FLAGS) -o pruebas *.c

execute: build
	./pruebas

valgrind: build
		$(VALGRIND) ./pruebas

gdb: build
	$(GDB) pruebas

entrega: *.c *.h
		$(CC) $(FLAGS_ENTREGA) -o pruebas *.c


clean:
	rm -f pruebas
