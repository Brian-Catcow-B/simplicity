CC = gcc
CFLAGS = -Wall -Wextra -g

PROJECT = simplicity

SRC = src
INCLUDE = inc
OBJ = objects
BIN = bin

SRC_FILES = $(SRC)/game.c $(SRC)/misc.c $(SRC)/creature.c
OBJ_FILES = $(OBJ)/game.o $(OBJ)/misc.o $(OBJ)/creature.o

all: mkdirs $(PROJECT)

$(PROJECT): $(OBJ_FILES) $(SRC)/main.c
	$(CC) -c $(OBJ_FILES) -o $(PROJECT) $^

mkdirs:
	mkdir -p $(SRC)
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $^
	mv *.o $(OBJ)/

clean:
	rm -rf $(OBJ)/* $(BIN)/*
