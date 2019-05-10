cmake_minimum_required (VERSION 2.6)
project (my_engine)

set(CMAKE_CXX_STANDARD 11)

# source files for the engine
file(GLOB ENGINE_SOURCES "src/*.cpp")
file(GLOB IMGUI_SOURCES "src/imgui/*.cpp")
add_library(myengine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES})

set (OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

IF (WIN32)
# Imm32 is required for imgui
    target_link_libraries(myengine Imm32 mingw32)
ENDIF()

# mingw32 should be before SDL2main
target_link_libraries(myengine SDL2main SDL2 ${OPENGL_LIBRARIES})

