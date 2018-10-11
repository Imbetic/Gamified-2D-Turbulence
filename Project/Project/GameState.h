#pragma once

#include "State.h"
#include "Cell.h"

class GameState: public State
{
private:

	int m_gridx;
	int m_gridy;

	Cell* m_cells;
	int m_numberofcells;

public:

	GameState();
	~GameState();

	void Create(int p_gridx, int p_gridy);
	void Initialize();
	void Update();
	void Draw();
	void Exit();
};

