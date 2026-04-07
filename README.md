# Command & Conquer Red Alert — macOS Port

A work-in-progress port of Command & Conquer Red Alert to **macOS** using **Raylib** for rendering/input/audio and **Zig** as the build system.

The original source code was released by EA under GPL v3. This fork takes the ~572 C++ files and ~268 x86 ASM files from 1996 and makes them compile and run on modern macOS (Apple Silicon / x86_64).

## Current Status

- **Compiles and links** on macOS with zero errors (Zig + clang)
- **Game initializes** — MIX archives load, RULES.INI parses, fonts init
- **Title screen renders** — 8-bit palettized framebuffer displayed via Raylib
- **Main menu interactive** — mouse clicks detected, menu buttons work
- **Audio plays** — Westwood AUD format (IMA ADPCM) decoded and streamed
- **Input works** — keyboard and mouse mapped from Raylib to game's VK_ codes

### What's Not Done Yet

- In-game rendering (scenario loading after menu)
- Proper bitmap font rendering (game's FNT format partially implemented)
- VQA movie playback
- Multiplayer networking
- Full audio streaming (currently uses pre-decoded WAV)

## Architecture

The port follows a **non-invasive** approach — original sources stay mostly untouched, with the port living in `macredalert/`:

```
CnC_Red_Alert/
├── CODE/              ← original game source (minimal changes)
├── WIN32LIB/          ← original Win32 libraries (minimal changes)
└── macredalert/       ← the macOS port
    ├── build.zig      ← Zig build system
    ├── src/
    │   ├── platform/  ← Raylib backends (video, input, audio, entry point)
    │   ├── compat/    ← Win32 API shim, ASM reimplementations in C
    │   └── stubs/     ← fake Windows/DOS headers
    └── build.zig.zon
```

### Key Techniques

- **Win32 API shim** (`platform.h`) — 1200+ lines mapping Windows types and functions to POSIX/macOS equivalents
- **ASM → C rewrite** — all x86 assembly (graphics primitives, LCW compression, shape drawing) reimplemented in portable C
- **8-bit → RGBA pipeline** — game renders to RAM buffers at 640×400 @ 8bpp, converted via palette LUT, displayed through Raylib `Texture2D`
- **MIX archive I/O** — CRC-based file lookup fixed for 64-bit (original used `long` which is 8 bytes on arm64)

## Building

### Prerequisites

- [Zig](https://ziglang.org/download/) (0.15+)
- [Raylib](https://www.raylib.com/) (installed via Homebrew: `brew install raylib`)
- Game data files from a legal copy of Red Alert ([Steam](https://store.steampowered.com/bundle/39394/Command__Conquer_The_Ultimate_Collection/) or [EA App](https://www.ea.com/en-gb/games/command-and-conquer/command-and-conquer-the-ultimate-collection/buy/pc))

### Build & Run

```bash
cd macredalert
zig build

# Copy game data files (MIX archives) to the build output directory
cp /path/to/redalert/data/*.MIX zig-out/bin/

# Run
./zig-out/bin/redalert
```

Raylib paths default to Homebrew's Apple Silicon location (`/opt/homebrew/`). Override with:

```bash
zig build -Draylib-include=/path/to/raylib/include -Draylib-lib=/path/to/raylib/lib
```

## Original Source

This is a fork of [EA's official release](https://github.com/electronicarts/CnC_Red_Alert) of the Command & Conquer Red Alert source code under GPL v3. See [LICENSE.md](LICENSE.md) for details.

To use the compiled game, you must own a legal copy of Command & Conquer Red Alert.
