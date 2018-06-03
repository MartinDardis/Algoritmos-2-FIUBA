CC = gcc
FLAGS = -g -Wall -Wconversion -Wtype-limits -pedantic -Werror
FLAGS_ENTREGA = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
GDB = gdbgui
ARCHIVOS_C = pruebas_abb_alumno.c abb.c testing.c lista.c

cpruebas: $(ARCHIVOS_C)
	$(CC) $(FLAGS) $(ARCHIVOS_C) -o pruebas
	./pruebas

valgrind: pruebas
	$(CC) $(FLAGS) $(ARCHIVOS_C) -o pruebas
	$(VALGRIND) ./pruebas

gdb: pruebas
	$(GDB) pruebas

clean:
		rm pruebas
		rm *.o
