# Compilador C++
CXX = g++
# Flags de compilação base: -std=c++11 para C++11, -Wall para warnings
CXXFLAGS = -std=c++11 -Wall

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
TARGET = $(BIN_DIR)/pa3.out

# Headers - Listados como dependências para garantir a recompilação quando alterados
HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp) # Detecta todos os .hpp em include

# --- Configuração de Debug e Valgrind ---

# Define DEBUG=1 para habilitar flags de depuração (ex: make DEBUG=1)
# Se DEBUG=1, adiciona -g3 e remove otimizações (-O3), usando -O0.
# Se DEBUG não for definido (ou vazio), usa otimização -O3.
ifneq ($(DEBUG),)
    # Flags para Debug
    CXXFLAGS += -g3 # Adiciona símbolos de depuração
    CXXFLAGS += -O0 # Sem otimização
    BUILD_MODE = Debug
else
    # Flags para Release (padrão)
    CXXFLAGS += -O3 # Otimização máxima
    BUILD_MODE = Release
endif

# --- Regras de Compilação ---

# Regra padrão (o que é executado quando você digita apenas 'make')
# Constrói o executável final.
all: $(TARGET)
	@echo "Build concluído no modo: $(BUILD_MODE)"

# Regra para linkar os arquivos objeto e criar o executável final
$(TARGET): $(OBJS)
	@echo "Linkando para criar o executável: $@"
	mkdir -p $(BIN_DIR) # Cria o diretório bin se não existir
	$(CXX) $(CXXFLAGS) $^ -o $@ # Linka os objetos para criar o executável

# Regra genérica para compilar arquivos .cpp em arquivos .o
# Para cada .o em $(OBJS), ele encontra o .cpp correspondente em $(SRC_DIR)
# Depende do .cpp correspondente e de TODOS os headers no INCLUDE_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo "Compilando: $< -> $@"
	mkdir -p $(OBJ_DIR) # Cria o diretório obj se não existir
	$(CXX) $(CXXFLAGS) -c $< -I $(INCLUDE_DIR) -o $@ # Compila o .cpp para .o

# --- Regras Utilitárias ---

# Regra para limpar os arquivos gerados (objetos e executável)
clean:
	@echo "Limpando arquivos gerados..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR) # Remove os diretórios obj e bin

# Regra para executar o programa (constrói primeiro se necessário)
run: $(TARGET)
	@echo "Executando: $(TARGET)"
	@./$(TARGET)

# Regra para executar com Valgrind (constrói primeiro se necessário, sempre em modo Debug)
# Garante que a compilação seja feita com DEBUG=1
valgrind:
	@echo "Executando com Valgrind (garantindo compilação em modo Debug)..."
	@$(MAKE) all DEBUG=1 # Força a compilação com flags de debug
	valgrind --leak-check=full \
	          --track-origins=yes \
	          --show-leak-kinds=all \
	          ./$(TARGET)

# Declara alvos que não são arquivos (para evitar conflitos com nomes de arquivos)
.PHONY: all clean run valgrind

