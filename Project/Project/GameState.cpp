#include "GameState.h"



GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::Create(int p_gridx, int p_gridy)
{
	m_numberofcells = p_gridx*p_gridy;
	m_cells = new Cell[m_numberofcells];
	m_gridx = p_gridx;
	m_gridy = p_gridy;
}

void GameState::Initialize() 
{
	
}

void GameState::Update() 
{

}
void GameState::Draw() 
{

}

void GameState::Exit() 
{

}
