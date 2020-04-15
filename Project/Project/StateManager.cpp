#include "StateManager.h"
#include "GameState.h"


StateManager::StateManager()
{
	m_DrawManager = nullptr;
	m_currentstate = nullptr;
}


StateManager::~StateManager()
{
	m_currentstate->Exit();
	delete m_currentstate;
}

void StateManager::Initialize(DrawManager p_DrawManager)
{
	m_currentstate = new GameState;
	m_DrawManager = &p_DrawManager;
	m_currentstate->Initialize();
}

bool StateManager::Update(float deltatime)
{
	m_currentstate->Update(deltatime);
	m_currentstate->Draw(*m_DrawManager);
	return false;
}