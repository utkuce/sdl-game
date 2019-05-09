#include <iostream>

#include "engine.h"

SDL_Window *window;
SDL_GLContext glcontext;

void initialize(int width, int height)
{
	ImGui::CreateContext();
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		exit(1);
	}

	// Create window
	int flags = SDL_WINDOW_OPENGL;
	if (Renderer::fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  width, height, flags);

	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		SDL_Quit();
		exit(1);
	}

	// Create GL context
	glcontext = SDL_GL_CreateContext(window);
	if (glcontext == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		SDL_Quit();
		exit(1);
	}

	// set vsync default value
	SDL_GL_SetSwapInterval(Renderer::vsync);

	// initialize renderer
	Renderer::init(window, width, height);

	// init imgui
	Interface::init(window, glcontext);
}

void gameFrame() 
{
	EventHandler::eventLoop();
	Renderer::render();
}

void gameLoop()
{
	#if __EMSCRIPTEN__
    	emscripten_set_main_loop(gameFrame, -1, 1);
	#else
		while (EventHandler::quitGame == false)
		{
			gameFrame();	
		}
	#endif
}

void finish()
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void start()
{
	initialize(1280,720);
	gameLoop();
	finish();
}