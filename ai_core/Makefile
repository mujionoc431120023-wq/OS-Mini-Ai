# ============================================================
# OS-MINI AI Makefile
# Compiles the enhanced AI system with all modules
# ============================================================

CC = gcc
CFLAGS = -Wall -Wextra -I./include -std=c99
LDFLAGS = -lncurses -lcurl -lpthread

# Source files - intelligence modules
INTELLIGENCE_SRC = src/intelligence/blackbox.c \
                   src/intelligence/fuzzy.c \
                   src/intelligence/context.c \
                   src/intelligence/language.c \
                   src/intelligence/sentiment.c \
                   src/intelligence/persistence.c \
                   src/intelligence/iot_controller.c \
                   src/intelligence/self_repair.c

# Source files - utility modules
UTILS_SRC = src/utils/security.c \
            src/utils/cloud_sync.c \
            src/utils/ota_update.c \
            src/utils/face_auth.c \
            src/utils/billing.c

# Source files - core modules
CORE_SRC = src/ai_hub.c \
           src/codeagent.c

# Main entry point
MAIN_SRC = src/main.c

# Object files
OBJ = $(INTELLIGENCE_SRC:.c=.o) $(UTILS_SRC:.c=.o) $(CORE_SRC:.c=.o)

# Target executable
TARGET = os-mini-ai

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ) $(MAIN_SRC)
	$(CC) $(MAIN_SRC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "=========================================="
	@echo "Build successful!"
	@echo "Run with: ./$(TARGET)"
	@echo "=========================================="

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)
	@echo "Clean complete!"

# Create data directory
setup:
	mkdir -p data

# Run the AI
run: $(TARGET)
	./$(TARGET)

# Help
help:
	@echo "OS-MINI AI Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all     - Build the AI system (default)"
	@echo "  setup   - Create data directory"
	@echo "  run     - Build and run"
	@echo "  clean   - Remove build files"
	@echo "  help    - Show this help"

.PHONY: all clean setup run help

