# Compiler and flags
CXX = g++
CXXFLAGS = -I/opt/homebrew/include/SDL2 -std=c++17 -Wall -Wextra
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer

# Directories
SRC_DIR = src
ENGINE_DIR = src/engine
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRC = $(SRC_DIR)/main.cpp \
      $(ENGINE_DIR)/engine.cpp \
      $(ENGINE_DIR)/input.cpp \
      $(ENGINE_DIR)/texture.cpp \
      $(ENGINE_DIR)/entity.cpp \
      $(ENGINE_DIR)/collision.cpp \
      $(ENGINE_DIR)/animation.cpp \
      $(ENGINE_DIR)/audio.cpp \
      $(ENGINE_DIR)/camera.cpp

# Object files
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/main

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned build artifacts."
