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
<<<<<<< Updated upstream
	int i = 0;
	if (p_cell.m_water == 1)
	{
		i = 0;
	}
	int j = 0;
	if (p_cell.m_water == 0)
=======
	
	/*if (p_cell.m_gas > 1)
	{
		i = (p_cell.m_gas - 1) / 5;
		j = (p_cell.m_gas - 1) / 5;

		if (p_cell.m_gas > 5)
		{
			i = 1;
			j = 1;
		}

	}
	else
	{
		i = 0;
		j = 0;
	}*/

	

		
	//int i = p_cell.m_gas2 * 255;
	int i = 0;
	int j = 0;
	int b = p_cell.m_gas * 255;
	
	if (b > 255)
>>>>>>> Stashed changes
	{
		j = 0;
	}
<<<<<<< Updated upstream
	SDL_SetRenderDrawColor(renderer, 255*i, 255*j, 255 * p_cell.m_water, 255);
=======
	//if (b < 0)
	//{
	//	b = 0;
	//}

	if (i > 255)
	{
		i = 255;
	}

	SDL_SetRenderDrawColor(renderer, i, 255*j, b, 255);
>>>>>>> Stashed changes
	SDL_RenderFillRect(renderer, &p_cell);

}

void DrawManager::Present()
{
	SDL_RenderPresent(renderer);
}