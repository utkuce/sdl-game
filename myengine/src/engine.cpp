#include <iostream>

#include "engine.h"

SDL_Window *window;
SDL_GLContext glcontext;

void initialize(int width, int height)
{
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

	SDL_GL_SetSwapInterval(Renderer::vsync);
	Renderer::init(window, width, height);
}

void gameLoop()
{
	while (!EventHandler::quitGame)
	{
		EventHandler::eventLoop();
		Renderer::render();
	}
}

void finish()
{
	for (int i = 0; i < Shape::render_list.size(); i++)
		delete Shape::render_list[i];

	ImGui_ImplSdl_Shutdown();
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