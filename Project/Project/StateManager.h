#pragma once

#include "State.h"
#include "DrawManager.h"

class StateManager
{
private:
	DrawManager* m_DrawManager;
	State* m_currentstate;
public:
	StateManager();
	~StateManager();


	void Initialize(DrawManager p_DrawManager);
	bool Update(float deltatime);
};

