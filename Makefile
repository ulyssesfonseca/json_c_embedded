# My first makefile

all: json_c

json_c: main.o json.o
	gcc -o json_c main.o json.o

main.o: main.c JSON/inc/JSON.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

json.o: JSON/src/JSON.c JSON/inc/JSON.h
	gcc -o json.o JSON/src/JSON.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ json_c

