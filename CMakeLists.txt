# Top-level build file for the term project.
# Build:  cmake -S . -B build && cmake --build build
# Test:   ctest --test-dir build --output-on-failure
cmake_minimum_required(VERSION 3.16)
project(TermProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Show more warnings so mistakes are found early.
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# The logic is split into libraries, one per layer. None of them uses raylib,
# so the tests build and run without a window. Each library links only to the
# layers below it:  core_util <- model <- sim <- app
# "model" holds both world/ and entities/ because World and Animal include
# each other, so they cannot be separate libraries.
add_library(core_util
    src/core/Vec2.cpp
    src/core/Position.cpp
    src/core/Random.cpp
)
target_include_directories(core_util PUBLIC src)

add_library(model
    src/world/Grid.cpp
    src/world/World.cpp
    src/world/Weather.cpp
    src/entities/Animal.cpp
    src/entities/Rabbit.cpp
    src/entities/Fox.cpp
)
target_link_libraries(model PUBLIC core_util)

add_library(sim
    src/sim/History.cpp
    src/sim/Simulation.cpp
    src/sim/BatchRunner.cpp
)
target_link_libraries(sim PUBLIC model)

# The GUI program. Only this target uses raylib, so the logic libraries and the tests
# build and run without a window. Turn the GUI off with: -DBUILD_GUI=OFF
option(BUILD_GUI "Build the raylib GUI program" ON)
if(BUILD_GUI)
    include(FetchContent)

    # FetchContent downloads raylib the first time you configure.
    # A fixed tag means both partners build the same version.
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    # raygui is one header file. We only need its "src" folder.
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
        GIT_SHALLOW TRUE)

    FetchContent_MakeAvailable(raylib raygui)

    add_executable(app
        src/main.cpp
        src/gui/App.cpp
        src/gui/GridView.cpp
        src/gui/PopulationGraph.cpp
        src/gui/ControlPanel.cpp
        src/gui/BatchResultsView.cpp
    )
    target_include_directories(app PRIVATE ${raygui_SOURCE_DIR}/src)
    target_link_libraries(app PRIVATE sim raylib)

    # raylib needs extra system frameworks on macOS.
    if(APPLE)
        target_link_libraries(app PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
    endif()
endif()

# Tests use doctest, a single-header test framework.
# FetchContent downloads it the first time you configure.
include(FetchContent)
# doctest asks for a very old CMake version. CMake 4 refuses that unless
# we set this. Older CMake versions ignore it.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(doctest)

enable_testing()
add_executable(unit_tests tests/test_main.cpp)
target_link_libraries(unit_tests PRIVATE sim doctest::doctest)
add_test(NAME unit_tests COMMAND unit_tests)
