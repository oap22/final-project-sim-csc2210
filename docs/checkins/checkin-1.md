# CSC 2210 Check-in 1 (Owen)

Owen Pacetti · 2026-11-05

## Prototype status

The GUI opens, but the simulation logic is not written yet. The sim classes are a scaffold of method signatures, and the GUI is not hooked up to them.

| Core feature | Status | Evidence |
| --- | --- | --- |
| Grid world (dirt, grass) | Scaffold only | [PR #6](https://github.com/oap22/final-project-sim-csc2210/pull/6), [`src/world/Grid.cpp`](../../src/world/Grid.cpp) |
| Grass spreads and is eaten | Not started | [`src/world/World.cpp`](../../src/world/World.cpp) |
| Rabbits move, eat, breed, die | Scaffold only | [`src/entities/Rabbit.cpp`](../../src/entities/Rabbit.cpp) |
| Foxes hunt rabbits | Scaffold only | [`src/entities/Fox.cpp`](../../src/entities/Fox.cpp) |
| Step loop with population counts | Scaffold only | [`src/sim/Simulation.cpp`](../../src/sim/Simulation.cpp) |
| GUI window with grid, controls, and graph | Partly (opens, not functional) | [PR #8](https://github.com/oap22/final-project-sim-csc2210/pull/8) |

How to run it on macOS, from the repo root:

```sh
xcode-select --install   # once, for the compiler
cmake -S . -B build
cmake --build build
./build/app
```

## My Git history

I opened and merged all of these PRs myself. [All merged PRs](https://github.com/oap22/final-project-sim-csc2210/pulls?q=is%3Apr+is%3Amerged)

| Merged | PR | What landed |
| --- | --- | --- |
| 2026-11-05 | [#8](https://github.com/oap22/final-project-sim-csc2210/pull/8) | GUI MVP (not functional yet) |
| 2026-11-04 | [#7](https://github.com/oap22/final-project-sim-csc2210/pull/7) | Directory restructure |
| 2026-11-02 | [#6](https://github.com/oap22/final-project-sim-csc2210/pull/6) | Class scaffold |
| 2026-11-02 | [#3](https://github.com/oap22/final-project-sim-csc2210/pull/3) | doctest for unit tests |
| 2026-11-02 | [#2](https://github.com/oap22/final-project-sim-csc2210/pull/2) | Windows MinGW g++ build steps in the README |
| 2026-10-26 | direct commit | Starter project layout |

## Tests

Claude generated these tests to show how doctest works. They test `Vec2` only, and `Vec2` does not relate to the project: nothing else in `src/` uses it. See [`tests/test_main.cpp`](../../tests/test_main.cpp).

| Test | Type | Expected | Actual | Pass/fail |
| --- | --- | --- | --- | --- |
| default Vec2 is zero | normal | x and y are 0 | x and y are 0 | Pass |
| Vec2 addition | normal | (1, 2) + (3, 4) = (4, 6) | (4, 6) | Pass |
| Vec2 scale | normal | (1, -2) × 3 = (3, -6) | (3, -6) | Pass |
| Vec2 length | normal | length of (3, 4) is 5 | 5 | Pass |

Run on my Mac on 2026-11-05: 4 test cases, 5 assertions, all passed.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Current blocker

- Getting the grid to show up in the GUI.
- Figuring out how to actually run the simulation.

## Next steps until Check-in 2

- [ ] Get the grid to show up in the GUI.
- [ ] Let users change the grid.
- [ ] Run a simulation with the things on the grid.

## AI use

My [AI-use log](../ai-use-log.md) has six entries since the proposal, one for each change that landed. Max keeps his own log.
