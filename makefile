CC = gcc
CFLAGS = -ansi -pedantic -O -g -ggdb\
		 -Wall -Wextra -Werror\
		 -I. -I`xml2-config --cflags`
LDFLAGS = -L`xml2-config --libs`


.PHONY: all, clean

all: vega

vega: main.o vega.o http.o vega.h

main.o: main.c vega.h
	$(CC) $(CFLAGS) -c -o main.o main.c

vega.o: vega.c vega.h
	$(CC) $(CFLAGS) -c -o vega.o vega.c

http.o: http.c vega.h
	$(CC) $(CFLAGS) -c -o http.o http.c

clean:
	- rm -f vega *.o
