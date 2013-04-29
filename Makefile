OBJ = main.o
CFLAGS = -Wall -std=c99

all: bin

bin: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

clean:
	rm bin $(OBJ)