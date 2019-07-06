CC = gcc
LIB = ../ms/ms.a
SRC = $(wildcard src/*.c)
RES_OUT_SRC = res_out/ms-gtk-resources.c
RES_OUT = res_out/ms-gtk-resources.o
OBJ = $(SRC:.c=.o)
GTK = `pkg-config --cflags --libs gtk+-3.0`
BIN = ms-gtk


GLIB_COMPILE_RESOURCES = $(shell pkg-config --variable=glib_compile_resources gio-2.0)

resources = $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=res --generate-dependencies res/ms-gtk.gresource.xml)

$(RES_OUT_SRC): res/ms-gtk.gresource.xml $(resources)
	$(GLIB_COMPILE_RESOURCES) res/ms-gtk.gresource.xml --target=res_out/ms-gtk-resources.c --sourcedir=res --generate-source

$(RES_OUT): $(RES_OUT_SRC)
	$(CC) -c $(RES_OUT_SRC) -o $(RES_OUT) $(GTK)
%.o: %.c
	$(CC) -c $< -o $@ $(GTK)

$(BIN): $(OBJ) $(RES_OUT)
	$(CC) $(OBJ) $(LIB) $(RES_OUT) -o $(BIN) $(GTK)

.PHONY: clean all
all: $(BIN) $(RES_OUT)
clean: $(BIN) $(RES_OUT)
	@rm $(OBJ) $(BIN) $(RES_OUT) $(RES_OUT_SRC)