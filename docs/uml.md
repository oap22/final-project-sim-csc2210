# Ecosystem Simulator: class design (draft)

This is the first draft of the UML class diagram. It follows the proposal.
Items marked **(open)** wait for a team decision. See "Open questions" at the end.

GitHub shows the diagrams below as pictures. In VS Code, use a Markdown
preview extension that supports Mermaid. PNG copies for the report are in
`docs/uml-core.png` and `docs/uml-gui.png`. If you change the Mermaid code,
make the PNGs again (for example with https://mermaid.live).

## Two layers

The code has two layers:

1. **core** (the `core` library in `CMakeLists.txt`): all simulation logic.
   It does not include `raylib.h`. The tests and batch mode use only this layer.
2. **gui** (the `app` program): raylib drawing and input. It reads from core
   and calls core functions. Core never calls the GUI.

This split is why we can test the rules without a window, and why batch mode
can run fast.

## Core layer

```mermaid
classDiagram
    direction TB

    class Simulation {
        -Config config
        -Random random
        -World world
        -Weather weather
        -History history
        -int stepCount
        -int stepLimit
        +Simulation(const Config& config)
        +step() void
        +run(int steps) void
        +isFinished() bool
        +getWorld() World&
        +getHistory() const History&
        +getWeather() const Weather&
        +setStepLimit(int limit) void
    }

    class Config {
        <<struct>>
        +int gridWidth
        +int gridHeight
        +unsigned seed
        +double grassSpreadChance
        +double plantSpreadChance
        +int grassFood
        +int plantFood
        +int rabbitFood
        +int rabbitMaxAge
        +int foxMaxAge
        +int rabbitBirthEnergy
        +int foxBirthEnergy
        +double deathNutrients
        +int settleWindow = 500
        +double settleTolerance = 0.02
    }

    class Random {
        -std::mt19937 engine
        +Random(unsigned seed)
        +nextInt(int low, int high) int
        +chance(double probability) bool
        +shuffle(std::vector~Position~& list) void
    }

    class World {
        -Grid grid
        -std::vector~std::unique_ptr~Animal~~ animals
        -std::vector~std::unique_ptr~Animal~~ births
        +World(int width, int height)
        +getGrid() Grid&
        +addAnimal(std::unique_ptr~Animal~ animal) bool
        +addBirth(std::unique_ptr~Animal~ baby) void
        +animalAt(Position pos) Animal* (not owner)
        +isFree(Position pos) bool
        +step(Random& random, const Config& config, double growth) void
        +count() PopulationCounts
        -growPlants(Random& random, const Config& config, double growth) void
        -removeDead(const Config& config) void
        -addBirthsToWorld() void
    }

    class Grid {
        -int width
        -int height
        -std::vector~Tile~ tiles
        +Grid(int width, int height)
        +at(Position pos) Tile&
        +inBounds(Position pos) bool
        +neighbors(Position pos) std::vector~Position~
        +getWidth() int
        +getHeight() int
    }

    class Tile {
        <<struct>>
        +TileType type
        +double nutrients
    }

    class TileType {
        <<enumeration>>
        Dirt
        Grass
        Plant
    }

    class Position {
        <<struct>>
        +int x
        +int y
        +operator==(const Position& other) bool
    }

    class Animal {
        <<abstract>>
        #Position position
        #int energy
        #int age
        #bool alive
        +Animal(Position pos, int energy)
        +~Animal() virtual
        +act(World& world, Random& random, const Config& config)* void
        +species()* Species
        +isAlive() bool
        +die() void
        +getPosition() Position
        #moveTo(World& world, Position pos) void
        #getOlder(int maxAge) void
    }

    class Rabbit {
        +Rabbit(Position pos, int energy)
        +act(World& world, Random& random, const Config& config) void
        +species() Species
        -eat(Tile& tile, const Config& config) void
    }

    class Fox {
        +Fox(Position pos, int energy)
        +act(World& world, Random& random, const Config& config) void
        +species() Species
        -hunt(World& world, Random& random) bool
    }

    class Species {
        <<enumeration>>
        Rabbit
        Fox
    }

    class Weather {
        -WeatherType type
        -int stepsLeft
        +update(Random& random) void
        +setWeather(WeatherType type, int steps) void
        +getType() WeatherType
        +growthMultiplier() double
    }

    class WeatherType {
        <<enumeration>>
        Normal
        Rain
        Drought
    }

    class History {
        -std::vector~PopulationCounts~ records
        +record(const PopulationCounts& counts) void
        +getRecords() const std::vector~PopulationCounts~&
        +anyExtinct() bool
        +averageRatio(int firstStep, int lastStep) double
        +hasSettled(int window, double tolerance) bool
    }

    class PopulationCounts {
        <<struct>>
        +int step
        +int grass
        +int plants
        +int rabbits
        +int foxes
    }

    class BatchRunner {
        -Config baseConfig
        +BatchRunner(const Config& config)
        +run(const std::vector~double~& ratios, int steps) std::vector~BatchResult~
    }

    class BatchResult {
        <<struct>>
        +double startRatio
        +bool survived
        +bool settled
        +double finalRatio
        +History history
    }

    Simulation *-- Config
    Simulation *-- Random
    Simulation *-- World
    Simulation *-- Weather
    Simulation *-- History
    World *-- Grid
    World *-- "0..*" Animal : owns (unique_ptr)
    Grid *-- "width x height" Tile
    Tile --> TileType
    Animal <|-- Rabbit
    Animal <|-- Fox
    Animal --> Species
    Animal --> Position
    Animal ..> World : uses in act()
    Weather --> WeatherType
    History *-- "0..*" PopulationCounts
    BatchRunner ..> Simulation : makes one per ratio
    BatchRunner ..> BatchResult : returns
```

## GUI layer

```mermaid
classDiagram
    direction LR

    class App {
        -Simulation simulation
        -GridView gridView
        -PopulationGraph graph
        -ControlPanel controls
        -bool running
        +App(const Config& config)
        +run() void
        -handleInput() void
        -draw() void
    }

    class GridView {
        -Rectangle area
        -int tileSize
        +draw(const World& world) void
        +tileUnderMouse() std::optional~Position~
        +place(World& world, PlaceTool tool, Position pos) void
    }

    class PopulationGraph {
        -Rectangle area
        +draw(const History& history) void
    }

    class ControlPanel {
        -Rectangle area
        -PlaceTool selectedTool
        -int stepLimit
        +draw(bool running) ControlAction
        +getSelectedTool() PlaceTool
        +getStepLimit() int
    }

    class BatchResultsView {
        +draw(const std::vector~BatchResult~& results) void
    }

    class ControlAction {
        <<enumeration>>
        None
        Start
        Stop
        StepOnce
        Reset
    }

    class PlaceTool {
        <<enumeration>>
        Grass
        Plant
        Rabbit
        Fox
        Erase
    }

    App *-- Simulation
    App *-- GridView
    App *-- PopulationGraph
    App *-- ControlPanel
    GridView ..> World : reads and places
    PopulationGraph ..> History : reads
    ControlPanel --> PlaceTool
    ControlPanel --> ControlAction
    BatchResultsView ..> BatchResult : reads
```

## How to read the arrows

| Arrow | Name | Meaning in our code |
|---|---|---|
| `*--` (filled diamond) | composition | The class owns the part. The part is a member or a `unique_ptr`, and it is destroyed with the owner. |
| `<\|--` (hollow triangle) | inheritance | `Rabbit` and `Fox` are kinds of `Animal`. |
| `-->` | association | The class keeps or uses a value of that type. |
| `..>` (dashed) | dependency | The class uses the other class only as a function parameter or return value. It does not own it. |

In the class boxes: `+` is public, `-` is private, `#` is protected,
and a function in *italics* (written with `*` at the end in the Mermaid code) is pure virtual (`= 0`).

## Why the design looks like this

- **Inheritance only for animals.** Rabbits and foxes do the same kinds of
  things (move, eat, get older, have babies, die) but with different rules.
  `World` keeps one list of `Animal` pointers and calls `act()` on each one.
  This is the one place where polymorphism is needed.
- **Tiles are an enum, not classes.** A tile only holds data (type and
  nutrients). The grass and plant spread rules run in `World::growPlants`.
  A class for each tile type would add virtual calls on every tile, every
  step, for no gain.
- **Composition everywhere else.** `Simulation` has a `World`, a `Weather`,
  and a `History`. `World` has a `Grid`. These are plain members, so they are
  made and destroyed with their owner (RAII). No `new` or `delete`.
- **`std::unique_ptr<Animal>` in `World`.** We need pointers because the
  vector holds different types (`Rabbit`, `Fox`). `unique_ptr` says that the
  `World` is the only owner. When an animal is removed from the vector, it is
  deleted. `Animal` has a virtual destructor so the right destructor runs.
- **Raw `Animal*` only to look, never to own.** `animalAt()` returns a plain
  pointer (or `nullptr`). The caller must not delete it.
- **Births and deaths wait until the step ends.** Adding to or removing from
  `animals` while we loop over it can break the loop. During a step, a dead
  animal is only marked (`alive = false`), and a baby goes into `births`.
  After all animals act, `removeDead()` erases the dead ones (and adds
  nutrients to their tiles), then `addBirthsToWorld()` moves the babies in.
  This is the plan from the proposal's "Update order" challenge.
- **One `Random` with a seed.** All random choices use the same `Random`
  object. With the same seed, a run is the same every time, so tests can
  check exact results.
- **`Config` holds every number we tune.** Tests can make a small, simple
  config. Batch mode copies the base config and changes only the
  starting numbers.
- **The GUI only reads and calls.** `GridView::draw` takes a `const World&`,
  so the drawing code cannot change the simulation by mistake.

## One step, in order

`Simulation::step()`:

1. `weather.update(random)`
2. `world.step(random, config, weather.growthMultiplier())`
   1. `growPlants(...)`: grass and plants spread; nutrients make plants grow faster.
   2. Shuffle the animal order, then call `act()` on each animal that is alive.
   3. `removeDead(config)`
   4. `addBirthsToWorld()`
3. `history.record(world.count())`
4. `stepCount++`

## Where the course requirements show up

| Requirement | Where |
|---|---|
| `.h` / `.cpp` split | One header and one source file per class in `include/` and `src/` |
| Standard containers | `std::vector` in `Grid`, `World`, `History`; maybe `std::map` for batch results (open) |
| Inheritance and polymorphism | `Animal`, `Rabbit`, `Fox`, virtual `act()` |
| Composition | `Simulation`, `World`, `Grid`, `App` |
| Operator overloading | `Position::operator==` |
| Ownership and cleanup | `unique_ptr` in `World`; members destroyed with owners; no `new`/`delete` |
| Input validation and errors | `World::addAnimal` returns `false` for a full or out-of-bounds tile; `Grid` constructor throws `std::invalid_argument` for a size of 0 or less; `ControlPanel` keeps the step limit at 1 or more |
| Memory diagram (report) | Good candidate: `App` on the stack, `World` inside it, each `Animal` on the heap owned by a `unique_ptr`, destroyed in `removeDead()` or when `World` is destroyed |

## Who builds what (from the proposal)

| Owen | Maxim | Both |
|---|---|---|
| `Grid`, `Tile`, grass and plant spread, `Rabbit`, `GridView` and placement, `BatchRunner` | `Fox`, nutrients in `removeDead`, `Weather`, `ControlPanel`, `PopulationGraph`, `BatchResultsView` | `Animal`, `World`, `Simulation`, `History`, `Config`, `Random` |

## Open questions

These change the design, so the team must choose. The draft uses the
recommended answer for now.

1. **One animal per tile?** Recommended: yes. Then `animalAt()` and `isFree()`
   are simple, and a fox eats a rabbit by moving onto its tile.
2. **How far can an animal see?** Recommended: only the 8 tiles around it
   (`Grid::neighbors`). A larger sight range is a good tuning option later.
3. **How do animals reproduce?** Recommended: alone, when energy is above
   `birthEnergy`. The parent gives half its energy to the baby in a free tile
   next to it. Needing a mate is more real but harder.
4. **What does eating a plant do?** Recommended: the plant tile goes back to
   dirt, like grass, but gives `plantFood` (more than `grassFood`).
5. **Who starts rain and drought?** Recommended: random, inside
   `Weather::update`, with `setWeather()` so a GUI button or a test can force it.
6. **What does batch mode show?** Recommended: it runs with no window, then
   opens a window with `BatchResultsView` (final ratio for each starting
   ratio). Printing a table to the console is the fallback.
7. **What is the "ratio" in batch mode?** The starting foxes per rabbit
   (for example 0.05, 0.10, 0.15), with a fixed total grass and rabbit count?
8. **File input for the failure test.** The assignment wants a test for a
   failure condition like a missing file. Save and load is only a stretch
   goal. Option: load `Config` from a small text file, so there is a real
   "missing or bad file" test.
