CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I include

# Diretórios
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TEST_DIR = tests

# Arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Nome do executável principal
TARGET = sistema_smart_home

# Arquivos de teste(Doctests)
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_TARGET = run_tests

# Padrao
all: $(BUILD_DIR) $(TARGET)

# Criar diretório build se não existir
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

MAIN_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
MAIN_OBJECTS = $(MAIN_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compilação dos objetos principais
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# COmpilação da main
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build dos testes
tests: $(BUILD_DIR) $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: tests
	@echo "Running tests..."
	@./$(TEST_TARGET)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)

# Regra para limpar os objetos
distclean: clean
	rm -rf $(BUILD_DIR)

# Rebuild
rebuild: clean all

# Rebuild dos testes
rebuild-tests: clean tests
