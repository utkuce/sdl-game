#include "EventHandler.h"

bool EventHandler::quitGame = false;
const uint8_t* EventHandler::keystate;
std::vector<SDL_Scancode> EventHandler::pressed_keys;

EventHandler::mp EventHandler::mouse_position;

void EventHandler::eventLoop()
{
  pressed_keys.clear();

  SDL_Event e;
  while( SDL_PollEvent( &e ) != 0 )
  {
    EventHandler::processEvent(e);
    ImGui_ImplSDL2_ProcessEvent(&e);
  }

  keystate = SDL_GetKeyboardState(NULL);

  SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
  mouse_position.y = windowHeight - mouse_position.y;

  // scale for renderer resolution
  mouse_position.y *= rendererHeight / windowHeight;
  mouse_position.x *= rendererWidth / windowWidth;
}

void EventHandler::processEvent(SDL_Event& e)
{
  if (e.type == SDL_QUIT)
    quitGame = true;
  else if (e.type == SDL_KEYDOWN)
    pressed_keys.push_back(e.key.keysym.scancode);
}

bool EventHandler::keyPressed(SDL_Scancode key_code)
{
  return std::find(pressed_keys.begin(), pressed_keys.end(), 
                    key_code) != pressed_keys.end();
}
