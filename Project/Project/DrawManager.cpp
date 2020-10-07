#include "DrawManager.h"



DrawManager::DrawManager()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	screenSurface = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

}


DrawManager::~DrawManager()
{

}

void DrawManager::Clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderClear(renderer);
}

void DrawManager::Draw(Cell& p_cell)
{
	/*
	SDL_Rect heyyyyt;
	heyyyyt.h = p_cell.h;
	heyyyyt.w = 100;
	heyyyyt.x = 1;
	heyyyyt.y = 1;
	*/

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	//SDL_RenderClear(renderer);
	//float i = p_cell.m_gas2 * 255;
	
	//i = 0;
	float j = 0;

	double b = 4*((p_cell.m_gas)/(1+1*p_cell.m_gas));
	//b = p_cell.m_gas;

	float i = 1 * ((p_cell.m_gas2) / (1 + 1 * p_cell.m_gas2));

	if (b > 1)
	{
		b = 1;
	}
	
	if (i > 1)
	{
		i = 1;
	}
	
	SDL_SetRenderDrawColor(renderer, (int)(255), (int)(255), (int)(255), (int)(i*50));
	SDL_RenderFillRect(renderer, &p_cell);
	SDL_SetRenderDrawColor(renderer, (int)(205), (int)(164), (int)(222), (int)(b * 255));
	SDL_RenderFillRect(renderer, &p_cell);

}

void DrawManager::Present()
{
	SDL_RenderPresent(renderer);
}