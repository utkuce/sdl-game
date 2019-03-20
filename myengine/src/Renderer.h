#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Shape.h"
#include "Interface.h"

extern int windowWidth, windowHeight;
extern float rendererWidth, rendererHeight;

class Renderer
{
  public:
    static void render();
    static void init(SDL_Window*, float, float);
    static void translateCoords(float coords[2]);
    static void toggleFullscreen();

    static float frameRate;
    static bool vsync, fullscreen;

  private:
    static SDL_Window* window;
    static ImVec4 background;
};

#endif
