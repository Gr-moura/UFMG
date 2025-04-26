CXX = g++
CXXFLAGS = -O3

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

# List all object files needed
OBJS = $(OBJ_DIR)/pa2.o $(OBJ_DIR)/graph.o $(OBJ_DIR)/listaAdjacencia.o

.PHONY: all clean run

all: $(BIN_DIR)/pa2.out

# Link final executable with all object files
$(BIN_DIR)/pa2.out: $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

# Compile pa2.cpp
$(OBJ_DIR)/pa2.o: $(SRC_DIR)/pa2.cpp $(INCLUDE_DIR)/graph.hpp $(INCLUDE_DIR)/listaAdjacencia.hpp
	@$(CXX) $(CXXFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

# Compile graph.cpp
$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.cpp $(INCLUDE_DIR)/graph.hpp
	@$(CXX) $(CXXFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

# Compile listaAdjacencia.cpp
$(OBJ_DIR)/listaAdjacencia.o: $(SRC_DIR)/listaAdjacencia.cpp $(INCLUDE_DIR)/listaAdjacencia.hpp
	@$(CXX) $(CXXFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*

run: $(BIN_DIR)/pa2.out
	./$(BIN_DIR)/pa2.out
