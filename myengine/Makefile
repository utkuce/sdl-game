CXX = clang++ -std=c++11 -Wall

SDL_LIB = -lSDL2main -lSDL2

ifdef OS
#Windows

#mwindows for removing command line
#Imm32 is required for IMGUI
LDFLAGS = -lmingw32 -lImm32 -lopengl32 #-mwindows 
TARGET = bin/myengine.dll

else
#Linux

CXX += -fPIC
LDFLAGS = -lGL
TARGET = bin/libmyengine.so

endif

SOURCES = $(wildcard src/*.cpp) $(wildcard src/IMGUI/*.cpp)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

all: $(OBJECTS)
	@echo "$(GREEN_COLOR) --> Compiling myengine shared object$(NO_COLOR)"
	@mkdir -p bin
	$(CXX) -shared -o $(TARGET) $^ $(SDL_LIB) $(LDFLAGS)

obj/%.o: src/%.cpp mkdir_obj
	@echo "$(COMPILING)"
	$(CXX) -c $< -o $@ 

obj/%.o: src/IMGUI/%.cpp mkdir_obj
	@echo "$(COMPILING)"
	$(CXX) -c $< -o $@

mkdir_obj:
	@mkdir -p obj

clean:
	rm -f $(TARGET) obj/*.o

GREEN_COLOR= $(shell echo -e "\033[32;01m")
BLUE_COLOR = $(shell echo -e "\033[36;01m")
NO_COLOR= $(shell echo -e "\033[0m")

COMPILING = $(GREEN_COLOR) --> Compiling "$<"$(NO_COLOR)