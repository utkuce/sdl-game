cmake_minimum_required (VERSION 2.6)
project (my_engine)

file(GLOB ENGINE_SOURCES "src/*.cpp")
file(GLOB IMGUI_SOURCES "src/IMGUI/*.cpp")
add_library(myengine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES})
target_link_libraries(myengine SDL2main SDL2 GL)