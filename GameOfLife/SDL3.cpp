#include "GameOfLife.h"


void start_SDL3(SDL_Window* window, SDL_Renderer* renderer)
{
	//1). Initialize the graphics hardware.
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//2.) Open the physical OS window.		//3.) Create the hardware renderer (talks to GPU).


	if (!SDL_CreateWindowAndRenderer("Game Of Life", 1920, 1080, 0, &window, &renderer))
	{
		SDL_Log("Failed to create window/render: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	//4.) Create your digital canvas texture (set to STREAMING so you can edit pixels fast)
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 1920, 1080);
	if (!texture)
	{
		SDL_Log("Failed to create texture: %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
}