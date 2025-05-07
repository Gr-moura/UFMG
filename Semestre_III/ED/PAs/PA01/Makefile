CC = gcc
CFLAGS = -O3

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

.PHONY: all clean run

all: $(BIN_DIR)/pa1.out

$(BIN_DIR)/pa1.out: $(OBJ_DIR)/pa1.o
	@$(CC) $(CFLAGS) $(OBJ_DIR)/pa1.o -o $(BIN_DIR)/pa1.out

$(OBJ_DIR)/pa1.o: $(SRC_DIR)/pa1.c $(INCLUDE_DIR)/pa1.h 
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/pa1.c -I $(INCLUDE_DIR) -o $(OBJ_DIR)/pa1.o

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*

run: $(BIN_DIR)/pa1.out
	./$(BIN_DIR)/pa1.out

