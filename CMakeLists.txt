cmake_minimum_required(VERSION 3.16)
project("money-man")

#BASICALLY REALEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
SET(CMAKE_CXX_FLAGS "-g")

find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)

#creating the executable of the simple software renderer
include_directories(src/)
file(GLOB_RECURSE "money-man" SRC src/*.cpp)
add_executable(money-man ${money-man})

target_link_libraries(money-man LINK_PRIVATE "${SDL2}")
