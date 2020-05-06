#include "InputManager.h"
//#include <cstdlib>

#include <iostream>

InputManager::InputManager()
{
	for (int i = 0; i < 4; i++)
	{
		m_KeyClick[i] = false;
		m_KeyRelease[i] = false;
		m_KeyDown[i] = false;
	}
	m_MouseClick = false;
	m_MouseRelease = false;
	m_MouseDown = false;
}

void InputManager::Update()
{
	m_MouseClick = false;
	m_MouseRelease = false;

	m_RightMouseClick = false;
	m_RightMouseRelease = false;

	for(int i = 0; i<4;i++) 
	{
		m_KeyClick[i] = false;
		m_KeyRelease[i] = false;
	}

	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_MOUSEMOTION: 
		{
			m_MousePosition.m_x = m_event.motion.x; m_MousePosition.m_y = m_event.motion.y; 
			break; 
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (m_event.button.button == SDL_BUTTON_LEFT)
			{
				m_MouseClick = true;
				m_MouseDown = true;
			}
			else if (m_event.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightMouseClick = true;
				m_RightMouseDown = true;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			if (m_event.button.button == SDL_BUTTON_LEFT)
			{
				m_MouseRelease = true;
				m_MouseDown = false;
			}
			else if (m_event.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightMouseRelease = true;
				m_RightMouseDown = false;
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_w:
			{ 
				m_KeyClick[Key_W] = true;
				m_KeyDown[Key_W] = true;
				break;
			}
			case SDLK_a:
			{
				m_KeyClick[Key_A] = true;
				m_KeyDown[Key_A] = true;
				break;
			}
			case SDLK_s:
			{
				m_KeyClick[Key_S] = true;
				m_KeyDown[Key_S] = true;
				break;
			}
			case SDLK_d:
			{
				m_KeyClick[Key_D] = true;
				m_KeyDown[Key_D] = true;
				break;
			}
			}
			break;
		}
		case SDL_KEYUP:
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_w:
			{
				m_KeyRelease[Key_W] = true;
				m_KeyDown[Key_W] = false;
				break;
			}
			case SDLK_a:
			{
				m_KeyRelease[Key_A] = true;
				m_KeyDown[Key_A] = false;
				break;
			}
			case SDLK_s:
			{
				m_KeyRelease[Key_S] = true;
				m_KeyDown[Key_S] = false;
				break;
			}
			case SDLK_d:
			{
				m_KeyRelease[Key_D] = true;
				m_KeyDown[Key_D] = false;
				break;
			}
			}
			break;
		}
		}
		
	}
		
}