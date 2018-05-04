CC = gcc
FLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui

build: *.c *.h
	$(CC) $(FLAGS) *.c -o tail

execute: build
	./tail

valgrind: build
		$(VALGRIND) ./tail

gdb: build
	$(GDB) tail

entrega: *.c *.h
		$(CC) $(FLAGS_ENTREGA) -o pruebas *.c


clean:
	rm -f tail
	rm -f *.o
