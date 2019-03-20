#include "Renderer.h"

SDL_Window *Renderer::window;
int windowWidth, windowHeight;
float rendererWidth, rendererHeight;

ImVec4 Renderer::background = ImColor(114, 144, 154);

int numberOfFrames;
int startTime;

float Renderer::frameRate = -1;
bool Renderer::vsync = true;
bool Renderer::fullscreen = false;

void Renderer::translateCoords(float coords[2])
{
	// translate game coordinates to opengl and scales according to resolution
	// coordinates are hardcoded for renderer size and scaled before translation

    coords[0] *= windowWidth / rendererWidth;
    coords[1] *= windowHeight / rendererHeight;

    coords[0] = (float)(coords[0] - windowWidth / 2) / (windowWidth / 2);
    coords[1] = (float)(coords[1] - windowHeight / 2) / (windowHeight / 2);
}

void Renderer::init(SDL_Window *window, float width, float height)
{
    Renderer::window = window;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    rendererWidth = width;
    rendererHeight = height;

    numberOfFrames = 0;
    startTime = SDL_GetTicks();

    SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));

    ImGui::GetIO().IniFilename = NULL;
    ImGui_ImplSdl_Init(window);
}

void update_framerate()
{
    numberOfFrames++;
    int elapsedMS = SDL_GetTicks() - startTime;

    if (elapsedMS != 0)
    {
		double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
		double fps = numberOfFrames / elapsedSeconds;
		if (fps != 0)
			Renderer::frameRate = fps;

		// reset frame count every second
		if (elapsedMS > 1000)
		{
			startTime = SDL_GetTicks();
			numberOfFrames = 0;
			Interface::fps_display = Renderer::frameRate;
		}
    }

    Renderer::vsync = SDL_GL_GetSwapInterval();
}

void update_interface(SDL_Window *window)
{
    ImGui_ImplSdl_NewFrame(window);
    Interface::update();
    ImGui::Render();
}

void Renderer::render()
{
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.44, 0.56, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Shape *item : Shape::render_list)
    {
		item->update();
		item->draw();
    }

    update_framerate();
    update_interface(window);

    SDL_GL_SwapWindow(window);
}

void Renderer::toggleFullscreen()
{
    SDL_SetWindowFullscreen(Renderer::window,
			    Renderer::fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
