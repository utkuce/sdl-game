#ifndef ENGINE_H
#define ENGINE_H

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <SDL2/SDL.h>

#include "Renderer.h"
#include "EventHandler.h"

extern void start();

#endif