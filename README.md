# Project Title (TODO)

One or two sentences: what the program does and why. (TODO)

**Team:** Owen, Partner Name (TODO)
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
- macOS: Xcode Command Line Tools (`xcode-select --install`)
- Windows: Visual Studio Build Tools with "Desktop development with C++"

## Build

```sh
cmake -S . -B build
cmake --build build
```

## Run

```sh
./build/app          # macOS / Linux
build\Debug\app.exe  # Windows (Visual Studio generator)
```

To build only the simulation logic and tests (no window, no download):

```sh
cmake -S . -B build -DBUILD_GUI=OFF
```

## Test

```sh
ctest --test-dir build --output-on-failure
```

## Project layout

| Folder     | Contents                                         |
|------------|--------------------------------------------------|
| `include/` | Header files (`.h`): class declarations          |
| `src/`     | Source files (`.cpp`): class definitions, `main` |
| `tests/`   | Unit tests                                       |
| `docs/`    | Proposal, diagrams, slides                       |

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
