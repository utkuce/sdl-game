CXX = clang++ -std=c++11

INCLUDE_PATH = -Imyengine/src
LIB_PATH = -Lmyengine/bin

MYENGINE = $(INCLUDE_PATH) $(LIB_PATH) -lmyengine
SDL_LIBS = -lSDL2main -lSDL2

SOURCES = $(wildcard src/*.cpp)

all: compile_myengine copy_runtime_libs
	@echo "$(GREEN_COLOR) -> Compiling game executable$(NO_COLOR)"

ifdef OS
#Compiling for windows
#library order matters
	$(CXX) $(SOURCES) -lmingw32 $(SDL_LIBS) $(MYENGINE) -o bin/mygame.exe
else
#Compiling for linux
	$(CXX) $(SOURCES) $(SDL_LIBS) $(MYENGINE) -o bin/mygame -Wl,-R bin
endif

copy_runtime_libs: compile_myengine
	@echo "$(COPYING_RUNTIME_LIBS)"

ifdef OS
#Windows
	cp -u C:/msys64/mingw64/bin/SDL2.dll bin/
	cp -u C:/msys64/mingw64/bin/libstdc++-6.dll bin/
	cp -u C:/msys64/mingw64/bin/libwinpthread-1.dll bin/
	cp -u C:/msys64/mingw64/bin/libgcc_s_seh-1.dll bin/
	cp -u myengine/bin/myengine.dll bin
else
#Linux
	cp -u myengine/bin/libmyengine.so bin
endif

compile_myengine: mkdir_bin
	@echo "$(BUILDING_ENGINE)"
	$(MAKE) -C myengine/

mkdir_bin:
	@mkdir -p bin

clean:
	rm bin/*
	$(MAKE) clean -C myengine


GREEN_COLOR= $(shell echo -e "\033[32;01m")
BLUE_COLOR = $(shell echo -e "\033[36;01m")
NO_COLOR= $(shell echo -e "\033[0m")

COPYING_RUNTIME_LIBS = $(BLUE_COLOR) -> Copying runtime libraries$(NO_COLOR)
BUILDING_ENGINE = $(BLUE_COLOR) -> Building game engine library$(NO_COLOR)