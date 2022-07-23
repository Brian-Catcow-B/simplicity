CC = gcc
CFLAGS = -Wall -Wextra -g

PROJECT = simplicity

SRC = src
INCLUDE = inc
OBJ = objects
BIN = bin

OBJ_FILES = $(OBJ)/game.o $(OBJ)/misc.o $(OBJ)/creature.o

all: mkdirs $(PROJECT)

$(PROJECT): $(OBJ_FILES) $(OBJ)/main.o
	$(CC) -o $(PROJECT) $^
	mv $(PROJECT) $(BIN)/

mkdirs:
	mkdir -p $(SRC)
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $^
	mv *.o $(OBJ)/

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $^
	mv main.o $(OBJ)/

clean:
	rm -rf $(OBJ)/* $(BIN)/*
