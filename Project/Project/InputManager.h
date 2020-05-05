#pragma once
#include "SDL.h"
#include "Vector2.h"

enum KeyCode
{
	Key_W = 0,
	Key_A = 1,
	Key_S = 2,
	Key_D = 3
};

class InputManager
{
	
	SDL_Event m_event;
	
public:
	InputManager();
	bool m_KeyClick[4] = {false,false,false,false};
	bool m_KeyDown[4] = { false,false,false,false };
	bool m_KeyRelease[4] = { false,false,false,false };

	bool m_MouseClick = false;
	bool m_MouseDown = false;
	bool m_MouseRelease = false;
	Vector2 m_MousePosition;
	void Update();
};

