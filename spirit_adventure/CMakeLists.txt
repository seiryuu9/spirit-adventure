cmake_minimum_required(VERSION 4.0)
project(spirit_adventure C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# libraried (modules) c source files in src/ folder
add_library(game src/game.c)
add_library(map src/map.c)
add_library(player src/player.c)
add_library(save src/save.c)

# main program
add_executable(spirit_adventure main.c)

# connects the main program with the libraries defined above
target_link_libraries(spirit_adventure game map player save)

# header sourse files in include/ folder
target_include_directories(spirit_adventure PRIVATE include)
