CC = gcc
CFLAGS = -O3

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

bin = pa2

.PHONY: all cleanAll run debug

all: $(bin) 

$(bin): $(OBJ_DIR)/pa2.o $(OBJ_DIR)/graph.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/pa2.o $(OBJ_DIR)/graph.o -o $(bin)

$(OBJ_DIR)/pa2.o: $(SRC_DIR)/pa2.c $(INCLUDE_DIR)/graph.h 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pa2.c -I $(INCLUDE_DIR) -o $(OBJ_DIR)/pa2.o

$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.c $(INCLUDE_DIR)/graph.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/graph.c -I $(INCLUDE_DIR) -o $(OBJ_DIR)/graph.o

cleanAll:
	rm -f $(bin) $(OBJ_DIR)/*.o

run: $(bin)
	./$(bin)

debug: $(bin)
	g++ -g3 $(SRC_DIR)/pa2.c $(SRC_DIR)/graph.c -o $(bin) -I $(INCLUDE_DIR)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./pa2
