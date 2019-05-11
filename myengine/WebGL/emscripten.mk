CXX = em++ -std=c++11

SOURCES = $(wildcard ../src/*.cpp)  
SOURCES += $(wildcard ../../src/*.cpp)
SOURCES += $(wildcard ../src/imgui/*.cpp)

EMCC_FLAGS = -s USE_SDL=2 -s USE_WEBGL2=1 -s WASM=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1
EMCC_FLAGS += -s BINARYEN_TRAP_MODE=clamp --shell-file shell_minimal.html

all:
	$(CXX) $(SOURCES) $(INCLUDE) ${EMCC_FLAGS} -o index.html