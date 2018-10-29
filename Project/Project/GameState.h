#pragma once

#include "State.h"
#include "Cell.h"

class GameState: public State
{
private:

	int m_numberofcells[2];
	Cell** m_cells;

public:

	GameState();
	~GameState();

	void Create(int p_gridx, int p_gridy);
	void Initialize();
	void Update(float deltatime);
	void LateUpdate();
	void Draw(DrawManager &p_DrawManager);
	void Exit();
};

