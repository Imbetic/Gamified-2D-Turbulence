#pragma once
#include "DrawManager.h"
#include "InputManager.h"

class State
{

private:

	//ViewPort
	//WorldObjects
	//GUIObjects

public:

	State();
	~State();

	virtual void Initialize() = 0;
	virtual void Update(InputManager &p_InputManager, DrawManager& p_DrawManager, double deltatime) = 0;
	virtual void Draw(DrawManager &p_DrawManager) = 0;
	virtual void Exit() = 0;

};