# Compilador C++
CXX = g++
# Flags de compilação: -std=c++11 para usar recursos do C++11, -Wall para habilitar warnings, -O3 para otimização
CXXFLAGS = -std=c++11 -Wall -O3

# Diretórios
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

# Arquivos fonte .cpp (detecta automaticamente todos os .cpp em SRC_DIR)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto .o (gera a lista de .o correspondente aos .cpp)
# Ex: src/graph.cpp -> obj/graph.o
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Nome do executável final
TARGET = $(BIN_DIR)/pa2.out

# Headers - Lista explícita para referência, embora a regra de compilação use -I
HEADERS = $(INCLUDE_DIR)/graph.hpp $(INCLUDE_DIR)/listaAdjacencia.hpp $(INCLUDE_DIR)/listaEncadeada.hpp

# Regra padrão (o que é executado quando você digita apenas 'make')
all: $(TARGET)

# Regra para linkar os arquivos objeto e criar o executável final
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR) # Cria o diretório bin se não existir
	@$(CXX) $(CXXFLAGS) $^ -o $@

# Regra genérica para compilar arquivos .cpp em arquivos .o
# Para cada .o em $(OBJS), ele encontra o .cpp correspondente em $(SRC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) # Depende do .cpp e dos headers relevantes
	@mkdir -p $(OBJ_DIR) # Cria o diretório obj se não existir
	@$(CXX) $(CXXFLAGS) -c $< -I $(INCLUDE_DIR) -o $@

# Regra para limpar os arquivos gerados (objetos e executável)
clean:
	@rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

# Regra para executar o programa
run: $(TARGET)
	@./$(TARGET)

# Declara alvos que não são arquivos (para evitar conflitos com nomes de arquivos)
.PHONY: all clean run
