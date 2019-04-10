cmake_minimum_required (VERSION 2.6)
project (sdl_game)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory (myengine)

file(GLOB GAME_SOURCES "src/*.cpp")
add_executable(sdlgame ${GAME_SOURCES})
target_link_libraries(sdlgame myengine)

