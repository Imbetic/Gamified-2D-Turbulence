#include "Cell.h"



Cell::Cell()
{

}
//Teos10
Cell::~Cell()
{
}

void Cell::Initialize(Cell *p_top_neighbour, Cell *p_right_neighbour, Cell *p_bot_neighbour, Cell *p_left_neighbour)
{
	m_volume = 1;

	m_top_neighbour_cell = p_top_neighbour;
	m_right_neighbour_cell = p_right_neighbour;
	m_bot_neighbour_cell = p_bot_neighbour;
	m_left_neighbour_cell = p_left_neighbour;
}

void Cell::Receive(float p_water, float p_salt, float p_temperature)
{
	m_pending_water += p_water;
	//m_pending_salt += p_salt;
	//m_pending_temperature += p_temperature;
}

float Cell::MaxDensity(float p_pressure)
{
	return 1; //kg/liter
}

void Cell::Update()
{
	
}