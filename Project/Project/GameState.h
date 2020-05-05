#pragma once

#include "State.h"
#include "Cell.h"

class GameState: public State
{
private:

	double totalvolume;
	int m_numberofcells[2];
	Cell** m_cells;

public:

	GameState();
	~GameState();

	void Create(int p_gridx, int p_gridy);
	void Initialize();
	void Update(InputManager &p_InputManager, double deltatime);
	void LateUpdate();
	void Draw(DrawManager &p_DrawManager);
	void Exit();
};

