CXX = g++
CXXFLAGS = -std=c++11 -w -I include

# Flags para cobertura de código
COV_FLAGS = --coverage -g -O0

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

# Modo de cobertura
COVERAGE ?= 0

# Adiciona flags de cobertura se ativado
ifeq ($(COVERAGE),1)
    CXXFLAGS += $(COV_FLAGS)
    LDFLAGS = $(COV_FLAGS)
endif

# Padrao
all: $(BUILD_DIR) $(TARGET)

# Criar diretório build se não existir
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

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
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: tests

	@./$(TEST_TARGET)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)
	rm -f $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno

# Regra para limpar os objetos
distclean: clean
	rm -rf $(BUILD_DIR)

# Rebuild
rebuild: clean all

# Rebuild dos testes
rebuild-tests: clean tests

# ============================================
# REGRA DE COBERTURA COMPLETA
# ============================================
coverage: clean

	$(MAKE) COVERAGE=1 tests
	@./$(TEST_TARGET) 2>/dev/null || true
	@gcovr -r . --object-directory $(BUILD_DIR) --html --html-details -o coverage.html --gcov-ignore-parse-errors --exclude '$(TEST_DIR)/.*' --exclude '.*/doctest.h'
	@gcovr -r . --object-directory $(BUILD_DIR) --gcov-ignore-parse-errors --exclude '$(TEST_DIR)/.*' --exclude '.*/doctest.h'