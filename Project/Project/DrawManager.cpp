#include "DrawManager.h"



DrawManager::DrawManager()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	screenSurface = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

}


DrawManager::~DrawManager()
{

}

void DrawManager::Draw()
{

	SDL_Rect heyyyyt;
	heyyyyt.h = 100;
	heyyyyt.w = 100;
	heyyyyt.x = 1;
	heyyyyt.y = 1;


	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
	SDL_RenderFillRect(renderer, &heyyyyt);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);

}