all:
	gcc -std=c99 -Wall main.c -o main
clean:
	rm -rf *.o main