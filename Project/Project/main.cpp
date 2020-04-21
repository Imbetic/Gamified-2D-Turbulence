#define SDL_MAIN_HANDLED
#include "SDL.h"
//#undef main

#include "DrawManager.h"
#include "StateManager.h"
#include "Vector2.h"

//#include "stdafx.h"
#include <string>
#include <iostream>
#include <iomanip>

#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
	srand(time(NULL));

	bool running = true;
	DrawManager m_DrawManager;
	StateManager m_StateManager;

	m_StateManager.Initialize(m_DrawManager);

	double m_timer = 20;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	while (running)
	{

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (NOW - LAST) / (double)SDL_GetPerformanceFrequency();
		deltaTime *= 10;
		//deltaTime = 1 / 60;
		//std::cout << std::fixed << "TIME" << std::endl;
		//std::cout << std::fixed << std::setprecision(10) << deltaTime << std::endl;
		//deltaTime = 0.05;
		//std::cout << std::fixed << std::setprecision(10) << deltaTime << std::endl;

		m_DrawManager.Clear();
		m_StateManager.Update(deltaTime);
		m_DrawManager.Present();

		
		if (m_timer < 0)
		{
			//running = false;
		}
		
	}
	
	return 0;

}