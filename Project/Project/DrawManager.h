#pragma once

#include "SDL.h"

class DrawManager
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *screenSurface;

public:
	DrawManager();
	~DrawManager();

	void Draw();
};