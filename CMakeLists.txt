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

# "core" holds all program logic that does not draw to the screen.
# Keeping it in a library lets the tests use the same code as the program.
add_library(core
    src/Vec2.cpp
)
target_include_directories(core PUBLIC include)

# The GUI program. Only this target uses raylib, so "core" and the tests
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

    add_executable(app src/main.cpp)
    target_include_directories(app PRIVATE ${raygui_SOURCE_DIR}/src)
    target_link_libraries(app PRIVATE core raylib)

    # raylib needs extra system frameworks on macOS.
    if(APPLE)
        target_link_libraries(app PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
    endif()
endif()

# Tests
enable_testing()
add_executable(unit_tests tests/test_main.cpp)
target_link_libraries(unit_tests PRIVATE core)
add_test(NAME unit_tests COMMAND unit_tests)
