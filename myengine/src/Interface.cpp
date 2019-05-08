#include "Interface.h"
#include <iostream>

bool Interface::settings = false, Interface::debug = false;
int Interface::fps_display = 0;
std::string Interface::debugChannel = "";

void Interface::init(SDL_Window* window, SDL_GLContext glContext) 
{
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL2_Init();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    io.IniFilename = NULL;
}

void Interface::update()
{
  settings ^= EventHandler::keyPressed(SDL_SCANCODE_ESCAPE);
  debug ^= EventHandler::keyPressed(SDL_SCANCODE_GRAVE);

  if (settings)
  {
    ImGui::SetNextWindowSize(ImVec2(400, 500));
    ImGui::SetNextWindowPosCenter();
    ImGui::Begin("Settings", NULL, ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoCollapse);

    if (ImGui::Checkbox("Vertical Sync ", &Renderer::vsync))
      SDL_GL_SetSwapInterval(Renderer::vsync);

    if (ImGui::Checkbox("Fullscreen ", &Renderer::fullscreen))
      Renderer::toggleFullscreen();

    ImGui::SetCursorPos(ImVec2(320, 470));
    if (ImGui::Button("Quit Game"))
      EventHandler::quitGame = true;

    ImGui::End();
  }

  if (debug)
  {
    std::string s = "fps: " + std::to_string(fps_display) +
                    "\nvsync: " + (Renderer::vsync ? "on" : "off") +
                    "\nentity count: " + std::to_string(Shape::render_list.size()) +
                    debugChannel;

    ImGui::SetNextWindowSize(ImVec2(300, 150));
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoResize |
                               ImGuiWindowFlags_NoCollapse);
    ImGui::Text("%s", s.c_str());
    ImGui::End();
  }

  debugChannel = "";
}
