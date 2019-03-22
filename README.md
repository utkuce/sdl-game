# sdl-game

A small game if you can even call it that with minimal graphics and minimal physics to learn about `sdl2`. For the meantime the player can jump, bounce of the walls and has a shield.

## Build & Run

### Windows

- Install `MSYS2` and update its repositories per the insturctions [here](https://www.msys2.org/)
- Run the application `MSYS2 MinGW 64-bit`
- Install required packages
    - `pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-clang make `
- `cd` to the root of this repository (e.g. `cd /c/Users/<username>/Downloads/sdl-game`)
- `make && bin/mygame.exe`

### Linux

- Install [sdl2](https://www.libsdl.org/index.php) from your distributions repository.
- `cd` to the root of this repository
- `make && bin/mygame`


[![Demo Video](https://i.imgur.com/jR69fTk.png)](https://streamable.com/66bor "Demo Video")



