all:
	gcc -std=c99 -Wall -pedantic-errors main.c -o main
clean:
	rm -rf *.o main