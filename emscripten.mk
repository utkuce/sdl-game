CXX = emcc -std=c++11

SOURCES = $(wildcard src/*.cpp) $(wildcard myengine/src/*.cpp) $(wildcard myengine/src/IMGUI/*.cpp)
EMCC_FLAGS = -s USE_SDL=2 -s LEGACY_GL_EMULATION=1 -s GL_FFP_ONLY=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0

all:
	$(CXX) $(SOURCES) $(INCLUDE) ${EMCC_FLAGS} -o index.html