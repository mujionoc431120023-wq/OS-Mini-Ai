# OS-MINI AI

## Dua Versi

OS-Mini Ai tersedia dalam dua versi:
1. **Custom Kernel** - OS kernel 32-bit x86 sendiri
2. **Linux Edition** - Aplikasi AI yang berjalan di Linux dengan CodeAgent

---

## 📗 Versi 1: Custom Kernel (Original)

### Struktur Folder

```
/kernel
├── arch/x86/       # Boot & console x86
├── core/            # Kernel, scheduler, paging, ELF loader
├── drivers/         # RAMFS
├── gui/             # Framebuffer & font
├── fonts/           # 8x8 bitmap font
├── include/         # Header files
├── user/            # User space apps (crt0, IPC client)
├── tools/           # Embed binary tool
├── Makefile
└── linker.ld
```

### Build Kernel

```bash
# Install dependencies
sudo apt-get install gcc-multilib make

# Build kernel
make

# Output: kernel.elf, kernel.bin
```

### Run di QEMU

```bash
qemu-system-i386 -kernel kernel.bin -m 256M -serial stdio
```

### User Apps Build

```bash
# Install cross-compiler
sudo apt-get install gcc-i386-elf

# Build user ELF
i386-elf-gcc -m32 -ffreestanding -nostdlib -c user/ipc_client.c -o ipc_client.o
i386-elf-gcc -m32 -c user/crt0.S -o crt0.o
i386-elf-ld -m elf_i386 -Ttext 0x10000 -o ipc_client.elf crt0.o ipc_client.o

# Embed ke C array
gcc -o tools/embed_bin tools/embed_bin.c
./tools/embed_bin user/ipc_client.elf kernel/user/ipc_client_bin.c ipc_client_bin
```

---

## 📘 Versi 2: Linux Edition (with CodeAgent)

Aplikasi AI lengkap yang berjalan di Linux dengan fitur CodeAgent untuk menangani tugas coding kompleks.

### Struktur Folder

```
/src
├── main.c           # Aplikasi CLI utama
├── ai_hub.c         # Semua modul AI
├── codeagent.c      # CodeAgent untuk coding
├── Makefile
└── os-mini-ai       # Executable (hasil build)

/include
└── ai_hub.h         # Header dengan deklarasi AI
```

### Build

```bash
cd src
make
```

### Run Interaktif

```bash
cd src
./os-mini-ai
```

### CLI Mode

```bash
# Health AI
./os-mini-ai --health "demam"
./os-mini-ai --health "batuk"

# Education AI
./os-mini-ai --edu "matematika"

# CodeAgent - Analyze
./os-mini-ai --codeagent "algorithm"
./os-mini-ai --codeagent "performance"
./os-mini-ai --codeagent "security"

# CodeAgent - Generate Code
./os-mini-ai --codegen c "linked list"
./os-mini-ai --codegen python "web server"
./os-mini-ai --codegen javascript "async"

# CodeAgent - Debug
./os-mini-ai --debug "null pointer"
./os-mini-ai --debug "memory leak"
./os-mini-ai --debug "sql injection"

# CodeAgent - Review
./os-mini-ai --review "goto"
```

### Menu Interaktif

```
═══ PILIH DOMAIN AI ====
  [1] Healthcare AI     - Analisis kesehatan & diagnosis
  [2] Education AI      - Rekomendasi materi pembelajaran
  [3] Finance AI        - Analisis transaksi keuangan
  [4] Manufacturing AI  - Prediksi maintenance mesin
  [5] IoT AI            - Proses smart home & sensor
  [6] Smart City AI     - Transportasi, energi, lingkungan
  [7] Governance AI     - Compliance & kebijakan
  [8] Future AI        - Quantum, Neuromorphic, Autonomous
  [9] CodeAgent AI     - ANALISIS & GENERASI KODE
  [10] Roadmap         - Evolutionary roadmap
  [0] Exit
```

### Fitur CodeAgent

| Fitur | Deskripsi |
|-------|-----------|
| **Analyze** | Analisis tugas coding kompleks (algorithm, data structure, performance, security, dll) |
| **Generate** | Generate kode (C, Python, JavaScript) |
| **Debug** | Debug & fix error (null pointer, memory leak, dll) |
| **Review** | Review kode, temukan issue |
| **Optimize** | Optimasi performa kode |
| **Explain** | Jelaskan kode secara detail |

---

## Domain AI Tersedia

- **Healthcare** - Diagnosis medis
- **Education** - Rekomendasi materi belajar
- **Finance** - Analisis transaksi
- **Manufacturing** - Prediksi maintenance
- **IoT** - Smart home processing
- **Smart City** - Transport, energi, lingkungan
- **Governance** - Compliance check
- **Future AI** - Quantum, Neuromorphic, Autonomous
- **CodeAgent** - Complex coding tasks ⭐ NEW!

---

## Development

### Menambahkan Domain AI Baru

1. Tambah fungsi di `src/ai_hub.c`
2. Deklarasikan di `include/ai_hub.h`
3. Tambah routing di `ai_hub_request()`
4. Tambah menu di `src/main.c`

---

## Lisensi

MIT License

---

## Roadmap

```
v1.0 -> Unified AI OS (Custom Kernel)
v2.0 -> AI IoT & Smart City
v3.0 -> AI Global Governance  
v4.0 -> Future AI (Quantum, Neuromorphic)
v5.0 -> Linux Edition + CodeAgent ⭐
v6.0 -> Singularity & Consciousness
v7.0 -> Infinity & Parallel Reality
v8.0 -> Final Destiny AI
```

