# ============================================================
# OS-MINI AI Makefile
# Compiles the enhanced AI system with all modules
# ============================================================

CC = gcc
CFLAGS = -Wall -Wextra -I./ai_core/include -std=c99
LDFLAGS = -lncurses -lcurl -lpthread

# Source files
INTELLIGENCE_SRC = ai_core/src/intelligence/blackbox.c \
                   ai_core/src/intelligence/fuzzy.c \
                   ai_core/src/intelligence/context.c \
                   ai_core/src/intelligence/language.c \
                   ai_core/src/intelligence/sentiment.c \
                   ai_core/src/intelligence/persistence.c \
                   ai_core/src/intelligence/iot_controller.c

UTILS_SRC = ai_core/src/utils/security.c \
            ai_core/src/utils/cloud_sync.c \
            ai_core/src/utils/ota_update.c \
            ai_core/src/utils/face_auth.c \
            ai_core/src/utils/billing.c

CORE_SRC = ai_core/src/ai_hub.c \
           ai_core/src/codeagent.c

MAIN_SRC = ai_core/src/main.c

# Object files
OBJ = $(INTELLIGENCE_SRC:.c=.o) $(UTILS_SRC:.c=.o) $(CORE_SRC:.c=.o)

# Target executable
TARGET = os-mini-ai

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ) $(MAIN_SRC)
	$(CC) $(MAIN_SRC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

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
