CC = gcc
AR = ar
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB = ms.a

%.o: %.c
	$(CC) -c $< -o $@

$(LIB): $(OBJ)
	@cp src/ms.h .
	$(AR) rcs $@ $^

.PHONY: clean
clean: $(LIB)
	@rm ms.h $(LIB) $(OBJ)
