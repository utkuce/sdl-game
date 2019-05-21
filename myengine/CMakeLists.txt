cmake_minimum_required (VERSION 2.6)
project (my_engine)

set(CMAKE_CXX_STANDARD 11)

# source files for the engine
file(GLOB ENGINE_SOURCES "src/*.cpp")
file(GLOB IMGUI_SOURCES "src/imgui/*.cpp")
add_library(myengine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES})

# opengl libs
set (OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
target_link_libraries(myengine ${OPENGL_LIBRARIES})

# glew
find_package(GLEW REQUIRED)
include_directories(myengine ${GLEW_INCLUDE_DIRS})
target_link_libraries(myengine ${GLEW_LIBRARIES})

IF (WIN32)
# Imm32 is required for imgui
# mingw32 should be before SDL2main
    target_link_libraries(myengine Imm32 mingw32)
ENDIF()


# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(myengine ${SDL2_LIBRARIES})
