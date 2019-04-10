cmake_minimum_required (VERSION 2.6)
project (sdl_game)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory (myengine)

file(GLOB GAME_SOURCES "src/*.cpp")
add_executable(sdlgame ${GAME_SOURCES})
target_link_libraries(sdlgame myengine)

IF (WIN32)
    add_custom_command(TARGET sdlgame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different C:/msys64/mingw64/bin/SDL2.dll .
        COMMAND ${CMAKE_COMMAND} -E copy_if_different myengine/libmyengine.dll .
        )
ENDIF()
