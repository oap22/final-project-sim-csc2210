# CSC 2210 AI-Use Log

Owen Pacetti · last updated 2026-11-05

Every entry in this log is in my own words. Claude only formats it from what I tell it.

## Entry format

Each entry uses the same six fields, in this order.

```markdown
### YYYY-MM-DD: short title

- **Tool:** tool and model
- **What AI did:**
- **What I did:**
- **What I kept or changed:**
- **How I checked it:**
- **What I learned:**
```

## Entries

### 2026-10-26: Starter project layout

- **Tool:** Claude
- **What AI did:** Helped with the organization of the layout.
- **What I did:** I designed the starter project layout.
- **What I kept or changed:** I kept the layout that I designed after Claude helped with the refinement.
- **How I checked it:** I worked back and forth with the model making sure that I was critical of its work and used my judgment.
- **What I learned:** AI is great to help as a partner when planning and designing.

### 2026-11-02: Windows MinGW g++ build steps in the README (PR #2)

- **Tool:** Claude
- **What AI did:** Formatted the build steps and the README after I told it to.
- **What I did:** I wrote the Windows MinGW and g++ build steps and the README. They come from my own workflow and how I use CMake.
- **What I kept or changed:** I changed the CMake targets a bit since the repo structure was changing but I kept most of the sections since they were correct based on my notes.
- **How I checked it:** I checked it by testing the different sections on my Mac and my Windows machine.
- **What I learned:** AI is useful for formatting instructions that you have if your notes a bit messy or not as orgnaized.

### 2026-11-02: doctest for unit tests (PR #3)

- **Tool:** Claude
- **What AI did:** Scaffolded the doctest setup since I have not worked with doctest.
- **What I did:** I designed it.
- **What I kept or changed:** I kept it since we have not actually written real tests yet, just been working on getting the unit test MVP there to ensure that when we write real tests we are good.
- **How I checked it:** By building the unit tests and then running them to make sure I knew how to run them and how it works.
- **What I learned:** The structure of unit tests in C++ using doctest and how to compile and run them using CMake.

### 2026-11-02: Class scaffold (PR #6)

- **Tool:** Claude
- **What AI did:** Wrote the scaffold, which was just the method signatures. It did not write any of the actual code, create the attributes, or add any of the actual functionality. Just a pure scaffold, to save us time.
- **What I did:** I designed the UML, the classes, and the methods. I designed how the classes interact with each other and where the enumerations go.
- **What I kept or changed:** The only thing I changed was the structure of the directories. I didn't really change any of the files because I didn't have any need to.
- **How I checked it:** I cross-referenced the UML diagram with what it wrote.
- **What I learned:** AI is really good at scaffolding. If you give it a set plan, really take the time to design things, and write exactly what needs to be done, it can do a very good job.

### 2026-11-04: Directory restructure (PR #7)

- **Tool:** Claude
- **What AI did:** Moved the files around and fixed CMake targets
- **What I did:** I did the directory restructure design and research for common best practices for organization.
- **What I kept or changed:** I kept the structure but moved main to be in the `src` directory root.
- **How I checked it:** I made sure to try and compile and build again with the new structure and execute the program.
- **What I learned:** I learned that Claude as well as other AI tools are great at the tedious work that is easily verifiable.

### 2026-11-05: GUI MVP, not functional yet (PR #8)

- **Tool:** Claude
- **What AI did:** Worked on it with me, since raylib was new to me. Claude also found the open source rights to a font that we could use in the project for the GUI.
- **What I did:** Worked on it with Claude while I was trying to learn how raylib works.
- **What I kept or changed:** I ended up changing the fonts and the spacings by hand since they were not formatted well or were not tasteful.
- **How I checked it:** I worked through the changes and tested the compilation and the build process to make sure the GUI would open up and look correct.
- **What I learned:** That AI can be helpful when learning new programming APIs/libraries.

## Parts I did without AI

All of the project design and structure was designed by me. Max and I came up with the idea. I created the dummy config in order to test the GUI. I designed the project architecture split with the GUI and the simulation being separate UMLs to improve organization and structure. I wrote the PR's, commit messages, and branch names. I did all of the Git commands and setup. I also merged the PR's and reviewed them myself.
