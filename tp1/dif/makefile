CC = gcc
FLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui
SALIDA = diff

build: *.c
	$(CC) $(FLAGS) -c dif.c

execute: build
	$(CC) $(FLAGS) *.o -o $(SALIDA)
	./$(SALIDA)

valgrind: build
		$(VALGRIND) ./$(SALIDA)

gdb: build
	$(GDB) $(SALIDA)


entrega: *.c
		$(CC) $(FLAGS_ENTREGA) -o $(SALIDA) *.c


clean:
	rm -f $(SALIDA)
	rm -f *.o
