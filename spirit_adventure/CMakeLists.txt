cmake_minimum_required(VERSION 4.0)
project(spirit_adventure C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# libraries (modules) c source files in src/ folder
add_library(game src/game.c)
add_library(map src/map.c)
add_library(player src/player.c)
add_library(save src/save.c)
add_library(text src/text.c)

# main program
add_executable(adv main.c)

# connects the main program with the libraries defined above
target_link_libraries(adv game map player save text)

# header source files in include/ folder
target_include_directories(adv PRIVATE include)
