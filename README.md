# sdl-game

A small game if you can even call it that with minimal graphics and minimal physics to learn about `sdl2`. For the meantime the player can jump, bounce of the walls and has a shield.

## Requirements

### Windows

- Install `MSYS2` and update its repositories per the insturctions [here](https://www.msys2.org/)
- Assuming a 64 bit environment, run the application `MSYS2 MinGW 64-bit` and install required packages
```
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2 mingw-w64-x86_64-glew
``` 
### Linux

Install [sdl2](https://www.libsdl.org/index.php) development libraries from the repository of your choice.

## Build & Run

    $ git clone https://github.com/utkuce/sdl-game.git
    $ cd sdl-game/
    $ git submodule update --init
    $ cmake . -G "Unix Makefiles" && make
    $ /bin/sdlgame

## Demo
[Online Demo](https://utkuce.github.io/sdl-game/) compiled with [Emscripten](https://emscripten.org/) toolchain



