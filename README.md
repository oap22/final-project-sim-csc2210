# Project Title (TODO)

One or two sentences: what the program does and why. (TODO)

**Team:** Owen, Max
**Course:** MSOE CSC 2210, term project

## Features

- TODO
- TODO

## Requirements

- A C++17 compiler (g++, clang++, or MSVC)
- CMake 3.16 or newer
- Git (CMake uses it to download the libraries)
- Libraries (downloaded by CMake the first time you configure, no manual install):
  - [raylib](https://www.raylib.com/) 5.5: window, drawing, input
  - [raygui](https://github.com/raysan5/raygui) 4.0: buttons and sliders
  - [doctest](https://github.com/doctest/doctest) 2.4.11: unit tests
- macOS: Xcode Command Line Tools (`xcode-select --install`)
- Windows: MinGW-w64 g++ (for example from MSYS2) or Visual Studio Build Tools

## Build

```sh
cmake -S . -B build
cmake --build build
```

Windows with MinGW g++: tell CMake to use the MinGW tools. Without `-G`, CMake
can pick the Visual Studio generator instead.

```sh
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## Run

```sh
./build/app          # macOS / Linux
build\app.exe        # Windows, MinGW g++
build\Debug\app.exe  # Windows, Visual Studio generator
```

To build only the simulation logic and tests (no window, no raylib download):

```sh
cmake -S . -B build -DBUILD_GUI=OFF
```

## Test

```sh
ctest --test-dir build --output-on-failure
```

## Project layout

| Folder          | Contents                                                |
|-----------------|---------------------------------------------------------|
| `src/core/`     | Basic types: `Vec2`, `Position`, `Random`, `Config`     |
| `src/world/`    | Environment: grid, tiles, world, weather                |
| `src/entities/` | Animals: `Animal`, `Rabbit`, `Fox`                      |
| `src/sim/`      | Simulation loop, history, batch runs                    |
| `src/gui/`      | raylib screens and controls (only `app` uses these)     |
| `src/main.cpp`  | Program entry point                                     |
| `tests/`        | Unit tests                                              |
| `docs/`         | Proposal, diagrams, slides                              |

Each folder holds its `.h` and `.cpp` files together. Include with the
folder name, for example `#include "world/World.h"`.

CMake libraries: `core_util` <- `model` (world + entities) <- `sim` <- `app`.
`world/` and `entities/` share one library because `World` and `Animal`
include each other.

## Controls / Usage

TODO

## Team workflow

1. Pull the newest `main`: `git checkout main && git pull`
2. Make a branch for one task: `git checkout -b feature/short-name`
3. Commit small steps with clear messages.
4. Push: `git push -u origin feature/short-name`
5. Open a pull request. The partner reviews it, then merge.

## Lessons learned

TODO (useful for the lightning talk)
