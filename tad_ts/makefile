all: tab_simbolos.o test.c
	gcc tab_simbolos.o test.c -g -o test -Wall

tab_simbolos.o: tab_simbolos.c tab_simbolos.h
	gcc -c tab_simbolos.c -o tab_simbolos.o

clean:
	rm -f *.o test
