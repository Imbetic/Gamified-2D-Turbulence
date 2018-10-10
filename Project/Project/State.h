#pragma once

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
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Exit() = 0;

};