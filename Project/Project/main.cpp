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

int main(int argc, char *argv[])
{
	
	
	bool running = true;
	DrawManager m_DrawManager;
	StateManager m_StateManager;

	m_StateManager.Initialize(m_DrawManager);

	long last = 0;
	float deltaTime = 0.0;
	long now = 0;
	deltaTime = ((float)(now - last)) / 1000;

	float m_timer = 10;

	while (running)
	{
		SDL_Delay(1);
		m_timer -= deltaTime;

		now = SDL_GetTicks();

		if (now > last) {
			deltaTime = ((float)(now - last)) / 1000;
			last = now;
		}

		m_DrawManager.Clear();
		m_StateManager.Update(deltaTime);
		m_DrawManager.Present();

		std::cout << std::fixed << std::setprecision(5) << m_timer << std::endl;
		if (m_timer < 0)
		{
			running = false;
		}
		
	}
	
	return 0;

}