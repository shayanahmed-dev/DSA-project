cmake_minimum_required(VERSION 3.15)
project(SmartComplete LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(SMARTCOMPLETE_SANITIZE "Enable AddressSanitizer with GCC/Clang" OFF)
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(SMARTCOMPLETE_SANITIZE)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address,undefined)
  endif()
endif()
add_library(engine engine/AutocompleteEngine.cpp)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(smartcomplete main.cpp ui/TerminalUI.cpp ui/ThemeManager.cpp ui/TerminalInput.cpp)
target_link_libraries(smartcomplete PRIVATE engine)
add_executable(smartcomplete_tests tests/tests.cpp)
target_link_libraries(smartcomplete_tests PRIVATE engine)
add_executable(smartcomplete_benchmark benchmarks/benchmark.cpp)
target_link_libraries(smartcomplete_benchmark PRIVATE engine)
enable_testing()
add_test(NAME structures_and_engine COMMAND smartcomplete_tests)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# BEGINNER'S GUIDE TO CMakeLists.txt
# This file tells CMake how to configure and build the complete project.
#
# cmake_minimum_required(VERSION 3.15)
# Prevents CMake older than 3.15 from configuring the project.
#
# project(SmartComplete LANGUAGES CXX)
# Names the project and tells CMake that C++ is the programming language.
#
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# Select C++17 as the language version and do not silently fall back to an older
# standard or compiler-specific extensions.
#
# option(SMARTCOMPLETE_SANITIZE ...)
# Creates a build option that can enable AddressSanitizer and UndefinedBehavior-
# Sanitizer. It is OFF by default because it is only needed for extra checking.
#
# if(MSVC) / else()
# Uses Microsoft Visual C++ warning options in MSVC and portable GCC/Clang
# warning options for other supported compilers.
#
# add_compile_options(...)
# Applies warning or sanitizer flags to files compiled by this project.
#
# add_link_options(...)
# Applies link-time sanitizer flags. This is required in addition to compile
# options so the generated executable contains the sanitizer runtime handling.
#
# add_library(engine ...)
# Groups AutocompleteEngine.cpp into a library named engine. The application,
# tests, and benchmark can all reuse that library.
#
# target_include_directories(engine PUBLIC ...)
# Allows files that link to the engine library to find project headers using
# paths relative to the project source directory.
#
# add_executable(...)
# Creates the main application, test executable, or benchmark executable.
#
# target_link_libraries(...)
# Adds the engine library to each executable that needs it.
#
# enable_testing() / add_test(...)
# Registers the test executable with CTest.
#
# file(COPY data DESTINATION ...)
# Copies the dictionary directory beside the build output so programs can find
# data/words.txt when launched from CMake's build directory.
