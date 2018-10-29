#pragma once

#include "SDL.h"
#include "Cell.h"

class DrawManager
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *screenSurface;

public:
	DrawManager();
	~DrawManager();

	void Clear();
	void Draw(Cell& cell);
	void Present();
};