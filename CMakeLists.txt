cmake_minimum_required(VERSION 3.16)
project(TerminalGamePlain LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TerminalGame
    src/main.cpp
    src/Terminal.cpp
    src/Console/Cartridge.cpp
    src/TerminalCartridge.cpp
)

target_include_directories(TerminalGame PRIVATE include)

if (MSVC)
    target_compile_options(TerminalGame PRIVATE /W4)
else()
    target_compile_options(TerminalGame PRIVATE -Wall -Wextra -Wpedantic)
endif()
