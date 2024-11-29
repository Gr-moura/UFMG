CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -O2
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
bin = main

#In a Makefile, phony refers to targets that are not actual files 
# but rather labels for commands to execute. Phony targets are 
# typically used for actions like cleaning build artifacts, running tests, and so on.
.PHONY: all cleanAll cleanTemp run debug

all: $(bin) 

$(bin): $(OBJ_DIR)/main.o $(OBJ_DIR)/aluno.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/aluno.o -o $(bin)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/aluno.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/aluno.o: $(SRC_DIR)/aluno.cpp $(INCLUDE_DIR)/aluno.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/aluno.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/aluno.o

cleanAll:
	rm -f $(bin) $(OBJ_DIR)/*.o

cleanTemp:
	rm -f $(OBJ_DIR)/*.a1 $(OBJ_DIR)/*.s1 $(OBJ_DIR)/files.txt

run: $(bin)
	./$(bin)

debug: $(bin)
	g++ -g3 $(SRC_DIR)/main.cpp $(SRC_DIR)/aluno.cpp -o $(bin) -I $(INCLUDE_DIR)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main
