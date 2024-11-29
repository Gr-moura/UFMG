CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -O2
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
bin = vpl_execution

.PHONY: all clean test 

all: $(bin) 

$(bin): $(OBJ_DIR)/main.o $(OBJ_DIR)/list.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/list.o -o vpl_execution

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/list.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/list.o: $(SRC_DIR)/list.cpp $(INCLUDE_DIR)/list.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/list.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/list.o

clean:
	rm -f $(bin) $(OBJ_DIR)/*.o

test: $(bin)
	./$(bin)

