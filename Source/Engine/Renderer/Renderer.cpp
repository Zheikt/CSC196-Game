#include "Renderer.h"
#include <SDL2-2.28.0/include/SDL.h>
namespace Enginuity
{
	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };
	void CreateWindow(const std::string& title, int width, int height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
}
