#!/bin/bash
# ============================================================
# OS-MINI AI Installation Script
# Installs dependencies and compiles the AI system
# ============================================================

echo "╔═══════════════════════════════════════════════════════╗"
echo "║     OS-MINI AI OMECA - INSTALLATION SCRIPT          ║"
echo "╚═══════════════════════════════════════════════════════╝"

# Check if running as root or with sudo
if [ "$EUID" -ne 0 ]; then 
    echo "Note: Some commands may require sudo. Running apt without sudo..."
fi

# Update package list
echo ""
echo "[1/5] Updating package lists..."
sudo apt-get update -qq

# Install dependencies
echo ""
echo "[2/5] Installing system dependencies..."
sudo apt-get install -y \
    build-essential \
    gcc \
    make \
    libncurses5-dev \
    libncursesw5-dev \
    libcurl4-openssl-dev \
    python3 \
    python3-pip

# Create data directory
echo ""
echo "[3/5] Creating project directories..."
mkdir -p data

# Clean previous build if exists
echo ""
echo "[4/5] Cleaning previous builds..."
rm -f os-mini-ai ai_core/*.o ai_core/src/*.o ai_core/src/**/*.o 2>/dev/null

# Compile the AI system
echo ""
echo "[5/5] Compiling OS-MINI AI Omega..."
cd ai_core
make clean 2>/dev/null
make setup

if make; then
    echo ""
    echo "╔═══════════════════════════════════════════════════════╗"
    echo "║           INSTALLATION SUCCESSFUL!                    ║"
    echo "╚═══════════════════════════════════════════════════════╝"
    echo ""
    echo "To run the AI system, type:"
    echo "  ./ai_core/os-mini-ai"
    echo ""
    echo "Or use: cd ai_core && make run"
    echo ""
else
    echo ""
    echo "╔═══════════════════════════════════════════════════════╗"
    echo "║           INSTALLATION FAILED!                       ║"
    echo "╚═══════════════════════════════════════════════════════╝"
    echo ""
    echo "Please check the error messages above."
    echo "You may need to install additional dependencies."
    exit 1
fi

echo ""
echo "Installation complete!"
