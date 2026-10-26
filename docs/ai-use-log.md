# AI-use log

The course asks us to keep this log. Each **significant** use of AI gets one
entry. "Significant" means the AI output changed our code, design, tests,
or a document we hand in.

Rules from the assignment that we follow here:

- Do not make up results, checks, or reflections. If a field is not true yet,
  leave it as `TODO`.
- Each of us must be able to explain, trace, and change every line we submit
  without AI.
- If one of us did not use AI for a part, say so (see "No AI used" below).

## How to add an entry

Copy this block to the end of the "Entries" section and fill in every field.

```markdown
### YYYY-MM-DD: short title

- **Who / tool:** name, tool and model (for example "Owen, Claude")
- **Where:** file, function, or report section
- **Why:** what problem you wanted help with
- **What the AI gave:** one or two lines
- **What we kept or changed:** what we kept, what we rewrote, what we threw away
- **How we checked it:** build, test, docs, debugger, partner review, ...
- **What I learned:** one concrete thing
- **Excerpt (optional):**
  > Prompt: ...
  >
  > Response (cut): ...
```

## Entries

Entries 1 to 6 come from the AI chat threads Owen used on 2026-10-26.
The "What the AI gave" lines are taken from those threads. The fields marked
`TODO (Owen)` are for Owen to fill in, because only Owen knows the answer.

### 2026-10-26: 1. Choose the project idea

- **Who / tool:** Owen, Claude (claude.ai project chat)
- **Where:** project idea; proposal "Overview" and "Core features"
- **Why:** get project options and turn one into a clear scope
- **What the AI gave:** 5 game ideas and 5 simulation ideas. After Owen picked
  the predator-prey ecosystem, it asked questions about what the user sees and
  does, wrote Owen's answers back as one paragraph, and compared raylib, SFML,
  and Dear ImGui. It suggested the "settled" rule (average predator:prey ratio
  over the last 500 steps within 2% of the 500 steps before, and no population
  at zero) after Owen said to use its judgement. It gave a rough run-time
  guess for batch mode and said it was not measured.
- **What we kept or changed:** Owen chose the ecosystem sim and set the
  features: a GUI with the grid and a live graph, dirt, grass, plants,
  rabbits, solitary foxes, placing things, start and stop, a step limit,
  nutrients from dead rabbits and foxes, rain and drought, and a headless
  batch mode. Owen chose raylib. The 2% / 500-step rule is a starting value
  to test. TODO (Owen): anything you changed after that
- **How we checked it:** TODO (Owen). Note: the run-time guess is not checked
  yet. We must time one headless run.
- **What I learned:** TODO (Owen)
- **Excerpt:**
  > Prompt (Owen): "gui has a graph view next to the sim view. The user should
  > be able to place things and then stop and start the simulation. grass,
  > rabbits, foxes, and plants that grow. ..."
  >
  > Response (cut): "Four things are still open: 1. Grass vs. plants. How are
  > they different? ... 2. 'Thriving.' How does the program measure it? ..."

### 2026-10-26: 2. Write the proposal

- **Who / tool:** Owen, Claude (claude.ai project chat and a shared doc)
- **Where:** `Term-Project-Proposal` (all sections)
- **Why:** finish the proposal the same day
- **What the AI gave:** first an outline with guide questions, then (when Owen
  asked "start drafting the proposal and I will make corrections and edits")
  a full first draft. Later a check against the assignment: the draft was too
  long (4 pages, limit 2) and had a cut-order problem.
- **What we kept or changed:** Owen asked to change the work split so that
  both partners do parts of the simulation and the GUI, and asked for the
  easiest test framework (doctest was chosen). Owen added the partner's name.
  TODO (Owen): other edits you made, and the final cuts to 2 pages
- **How we checked it:** checked against the assignment text. TODO (Owen):
  your own read-through, partner review
- **What I learned:** TODO (Owen)
- **Excerpt:**
  > Prompt (Owen, doc comment): "make it so that we both do parts of both so
  > one does not just do one part."

### 2026-10-26: 3. Set up the repository and build

- **Who / tool:** Owen, Claude (claude.ai project chat; it pushed to this repo)
- **Where:** `CMakeLists.txt`, `README.md`, `.gitignore`, `include/Vec2.h`,
  `src/Vec2.cpp`, `src/main.cpp`, `tests/test_main.cpp`
- **Why:** get a build that works on macOS (Clang) and Windows (g++)
- **What the AI gave:** a starter layout: C++17, warning flags, a `core`
  library, the `app` program, a test program, and one example class (`Vec2`).
  It added raylib 5.5 and raygui 4.0 with CMake FetchContent. On branches it
  added Windows MinGW build steps to the README (`docs/windows-mingw`, PR #2)
  and switched the tests to doctest (`tests/doctest`, PR #3).
- **What we kept or changed:** TODO (Owen). `Vec2` is only an example and
  will be replaced by our own classes.
- **How we checked it:** the AI built the no-GUI version and ran the tests on
  Linux. It could not build the raylib GUI. Not checked yet on macOS or
  Windows. TODO (Owen and Maxim): build on your own computers and write the
  result here
- **What I learned:** TODO (Owen)

### 2026-10-26: 4. Class notes on inheritance and polymorphism

- **Who / tool:** Owen, Claude (claude.ai project chat)
- **Where:** personal study notes (not in this repo); used for the `Animal`,
  `Rabbit`, and `Fox` design
- **Why:** take notes in class and understand virtual functions before the design
- **What the AI gave:** a note on base and derived classes, access
  specifiers, `virtual` and `override`, abstract classes, virtual
  destructors, and object slicing, with small examples. It said the examples
  compile with `g++ -std=c++17 -Wall`.
- **What we kept or changed:** TODO (Owen)
- **How we checked it:** TODO (Owen): for example, compare with the lecture
- **What I learned:** TODO (Owen)

### 2026-10-26: 5. UML class diagram (in progress)

- **Who / tool:** Owen, Claude (claude.ai project chat)
- **Where:** UML class diagram (report "Design" section)
- **Why:** turn the proposal into classes before we write code
- **What the AI gave:** a first draft with two layers: `core` (simulation,
  no raylib) and `gui` (raylib). The draft is not final yet.
- **What we kept or changed:** TODO (Owen), when the design is done
- **How we checked it:** TODO (Owen)
- **What I learned:** TODO (Owen)

### 2026-10-26: 6. Check-in pages and this log

- **Who / tool:** Owen, Claude (claude.ai project chat)
- **Where:** `docs/ai-use-log.md`, `docs/checkins/`
- **Why:** have the check-in pages and the required log ready before Week 10
- **What the AI gave:** this log file with the fields from the assignment,
  entries 1 to 6 taken from the chat threads, and templates for Check-in 1,
  Check-in 2, and the Week 14 readiness check
- **What we kept or changed:** TODO (Owen)
- **How we checked it:** TODO (Owen): read each entry and compare it with
  what really happened
- **What I learned:** TODO (Owen)

## Maxim's entries

TODO (Maxim): add your own entries, or write "I did not use AI for ..." here.

## No AI used

List parts that we wrote with no AI help. This helps show who did what.

- TODO
