#ifndef INTERFACE_H
#define INTERFACE_H

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "Renderer.h"
#include "EventHandler.h"

#include <string>

class Interface
{
  public:
    static void init(SDL_Window*, SDL_GLContext);
    static void update();
    static bool settings, debug;
    static int fps_display;
    static std::string debugChannel;
};

#endif
