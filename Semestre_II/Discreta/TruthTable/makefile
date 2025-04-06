CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -O2 -Wno-unused-variable -Wno-return-type
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
bin = main
lib = TruthTable


#In a Makefile, phony refers to targets that are not actual files 
# but rather labels for commands to execute. Phony targets are 
# typically used for actions like cleaning build artifacts, running tests, and so on.
.PHONY: all cleanAll cleanTemp run debug

all: $(bin) 

$(bin): $(OBJ_DIR)/main.o $(OBJ_DIR)/$(lib).o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/$(lib).o -o $(bin)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/$(lib).hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/$(lib).o: $(SRC_DIR)/$(lib).cpp $(INCLUDE_DIR)/$(lib).hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(lib).cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/$(lib).o

cleanAll:
	rm -f $(bin) $(OBJ_DIR)/*.o

cleanTemp:
	rm -f $(OBJ_DIR)/*.a1 $(OBJ_DIR)/*.s1 $(OBJ_DIR)/files.txt

run: $(bin)
	./$(bin)

debug: $(bin)
	g++ -g3 $(SRC_DIR)/main.cpp $(SRC_DIR)/aluno.cpp -o $(bin) -I $(INCLUDE_DIR)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main
