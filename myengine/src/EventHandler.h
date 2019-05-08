#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>

#include "imgui/imgui.h"
#include "imgui_impl_sdl.h"
#include "Renderer.h"

class EventHandler
{
  public:
    static void eventLoop();
    static bool quitGame;

    static const uint8_t* keystate;
    static struct mp {int x, y;} mouse_position;
    static bool keyPressed(SDL_Scancode);

  private:
    static void processEvent(SDL_Event&);
    static std::vector<SDL_Scancode> pressed_keys;
};

#endif
