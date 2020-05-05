#pragma once

#include "State.h"
#include "DrawManager.h"
#include "InputManager.h"

class StateManager
{
private:
	DrawManager* m_DrawManager;
	InputManager* m_InputManager;
	State* m_currentstate;
public:
	StateManager();
	~StateManager();


	void Initialize(DrawManager &p_DrawManager, InputManager &p_InputManager);
	bool Update(float deltatime);
};

