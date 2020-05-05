#include "StateManager.h"
#include "GameState.h"

//All below for printf!!
#include <string>
#include <iostream>
#include <iomanip>

StateManager::StateManager()
{
	m_DrawManager = nullptr;
	m_currentstate = nullptr;
	m_InputManager = nullptr;
}


StateManager::~StateManager()
{
	m_currentstate->Exit();
	delete m_currentstate;
}

void StateManager::Initialize(DrawManager &p_DrawManager, InputManager &p_InputManager)
{
	m_currentstate = new GameState;
	m_DrawManager = &p_DrawManager;
	m_InputManager = &p_InputManager;
	m_currentstate->Initialize();
}

bool StateManager::Update(float deltatime)
{
	if (m_InputManager->m_MouseClick)
	{
		printf("Working here");
	}
	m_currentstate->Update(*m_InputManager, deltatime);
	m_currentstate->Draw(*m_DrawManager);
	return false;
}