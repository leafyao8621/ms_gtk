CC = gcc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB = ../ms/ms.a
BIN = test

%.o: %.c
	$(CC) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN)

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)
