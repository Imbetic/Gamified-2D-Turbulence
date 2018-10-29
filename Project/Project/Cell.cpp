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
	m_water = 0.5;
	m_velocity.m_x = 0;
	m_velocity.m_y = 0;
	m_pending_water = 0;
	m_excess_water = 0;

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

void Cell::Update(float deltatime)
{
	if (m_bot_neighbour_cell != nullptr)
	{
		if (m_bot_neighbour_cell->m_water < 1 && m_water>0)
		{
			m_velocity.m_y += deltatime/10;

			m_bot_neighbour_cell->Receive(m_velocity.m_y / 10, 0, 0);
			
			m_water -= m_velocity.m_y/10;
			if(m_water < 0)
			{
				m_water = 0;
			}
		}

	}
}

void Cell::LateUpdate()
{
	m_water += m_pending_water;
	m_pending_water = 0;
	if (m_water > 1)
	{
		m_excess_water += (m_water - 1);
		m_water = 1;
	}
}