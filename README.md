# sdl-game

A small game if you can even call it that with minimal graphics and minimal physics to learn about `sdl2`. For the meantime the player can jump, bounce of the walls and has a shield.

## Requirements

### Windows

- Install `MSYS2` and update its repositories per the insturctions [here](https://www.msys2.org/)
- Run the application `MSYS2 MinGW 64-bit`
- Install required packages
    - `pacman -S mingw-w64-x86_64-SDL2`
    - `pacman -S mingw-w64-x86_64-clang`
    - `pacman -S mingw-w64-x86_64-cmake`
    
### Linux

Install [sdl2](https://www.libsdl.org/index.php) development libraries and [clang](https://clang.llvm.org/) from the repository of your choice.

## Build & Run

- `cmake . -DCMAKE_CXX_COMPILER=clang++ -G "Unix Makefiles"` 
- `make`
- `./bin/sdlgame`

## Demo
[Online Demo](https://utku.website/sdl-game/) compiled with [Emscripten](https://emscripten.org/) toolchain



