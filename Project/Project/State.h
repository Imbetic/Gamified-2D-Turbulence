#pragma once
#include "DrawManager.h"

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
	virtual void Update(float deltatime) = 0;
	virtual void Draw(DrawManager& p_DrawManager) = 0;
	virtual void Exit() = 0;

};