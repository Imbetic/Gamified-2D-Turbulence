#include "Cell.h"
#include <cstdlib>


#include <string>
#include <iostream>
#include <iomanip>

Cell::Cell()
{
	m_velocity.m_x = 0;
	m_velocity.m_y = 0;
}
//Teos10
Cell::~Cell()
{
}

void Cell::Initialize(Cell *p_top_neighbour, Cell *p_right_neighbour, Cell *p_bot_neighbour, Cell *p_left_neighbour)
{
	
	m_volume = 1;
	//m_water = 0 + 0.4 / (double)((rand() % 4) + 1);
	m_water = 1;
	
	m_velocity.m_x = 0;
	m_velocity.m_y = 0;
	m_pressure = 0;
	m_total_pressure = 0;
	m_excess_water = 0;

	m_top_neighbour_cell = p_top_neighbour;
	m_right_neighbour_cell = p_right_neighbour;
	m_bot_neighbour_cell = p_bot_neighbour;
	m_left_neighbour_cell = p_left_neighbour;
	
}

double Cell::Receive(double p_water, Vector2 p_momentum)
{
	Vector2 t_vel = m_velocity * m_water;
	
	m_water += p_water;
	if (m_water <= m_volume)
	{
		Vector2 t_othervel = p_momentum * p_water;
		m_velocity = (t_vel + t_othervel)/m_water;
		return 0;
	}
	else
	{
		m_excess_water = m_water - m_volume;
		Vector2 t_othervel = p_momentum * (p_water - m_excess_water);
		m_water = m_volume;
		return m_excess_water;
	}

	//m_pending_salt += p_salt;
	//m_pending_temperature += p_temperature;
	//m_pending_force += p_watertoomuch
}

void Cell::AddForce(double p_upforce, double p_rightforce, double p_downforce, double p_leftforce)
{
	m_pressurized = true;
	m_pending_force_top += p_upforce;
	m_pending_force_right += p_rightforce;
	m_pending_force_bot += p_downforce;
	m_pending_force_left += p_leftforce;
	
}

float Cell::MaxDensity(double p_pressure)
{
	return 1; //kg/liter
}

void Cell::EarlyUpdate(double deltatime)
{
	m_velocity.m_y += (deltatime)*m_water;
	
}

void Cell::Update(double deltatime)
{
	if (m_water > 0)
	{
		if (m_velocity.m_y > 0)
		{
			if (m_bot_neighbour_cell != nullptr)
			{

				if (m_velocity.m_y*deltatime <= m_water)
				{
					m_excess_water = m_bot_neighbour_cell->Receive(m_velocity.m_y*deltatime, m_velocity);
					m_water -= m_velocity.m_y*deltatime;
				}
				else
				{
					m_excess_water = m_bot_neighbour_cell->Receive(m_water, m_velocity);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_water += m_excess_water;
					m_bot_neighbour_cell->AddForce(m_velocity.m_y/deltatime, 0, 0, 0);
					m_velocity.m_y = 0;
					//m_velocity.m_y -= m_excess_water;
					//std::cout << std::fixed << std::setprecision(5) << m_velocity.m_y << std::endl;
					
					
				}

			}
			else
			{
				m_velocity.m_y = 0;
			}
			
		}
		/*if (m_velocity.m_y < 0)
		{
			if (m_top_neighbour_cell != nullptr)
			{

				if (-m_velocity.m_y <= m_water)
				{
					m_excess_water = m_top_neighbour_cell->Receive(-m_velocity.m_y, m_velocity);
					m_water -= -m_velocity.m_y;
				}
				else
				{
					m_excess_water = m_top_neighbour_cell->Receive(m_water, m_velocity);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_top_neighbour_cell->AddForce(m_excess_water, 0, 0, 0);
					m_water += m_excess_water;
					m_velocity.m_y += m_excess_water;
				}
			}
		}
		if (m_velocity.m_x > 0)
		{
			if (m_right_neighbour_cell != nullptr)
			{

				if (m_velocity.m_x <= m_water)
				{
					m_excess_water = m_right_neighbour_cell->Receive(m_velocity.m_x, m_velocity);
					m_water -= m_velocity.m_x;
				}
				else
				{
					m_excess_water = m_right_neighbour_cell->Receive(m_water, m_velocity);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_right_neighbour_cell->AddForce(m_excess_water, 0, 0, 0);
					m_water += m_excess_water;
					m_velocity.m_x -= m_excess_water;
				}

			}
		}
		if (m_velocity.m_x > 0)
		{
			if (m_left_neighbour_cell != nullptr)
			{

				if (-m_velocity.m_x <= m_water)
				{
					m_excess_water = m_left_neighbour_cell->Receive(-m_velocity.m_x, m_velocity);
					m_water -= -m_velocity.m_x;
				}
				else
				{
					m_excess_water = m_left_neighbour_cell->Receive(m_water, m_velocity);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_left_neighbour_cell->AddForce(m_excess_water, 0, 0, 0);
					m_water += m_excess_water;
					m_velocity.m_x += m_excess_water;
				}

			}
		}*/
	}
	else
	{
		m_velocity.m_y = 0;
	}
}

void Cell::LateUpdate(double deltatime)
{
	//if (m_pressurized)
	{
		m_total_pressure = (m_pending_force_top + m_pending_force_right + m_pending_force_bot + m_pending_force_left);

		m_pressure_top = m_total_pressure - m_pending_force_top;
		m_pressure_right = m_total_pressure - m_pending_force_right;
		m_pressure_bot = m_total_pressure - m_pending_force_bot;
		m_pressure_left = m_total_pressure - m_pending_force_left;

		m_pending_force_top = 0;
		m_pending_force_right = 0;
		m_pending_force_left = 0;
		m_pending_force_bot = 0;

		m_pressurized = false;
	}

}

void Cell::LateUpdate2(double deltatime)
{
	//if (m_total_pressure > 0)
	//{
		if (m_bot_neighbour_cell != nullptr)
		{
			if (m_bot_neighbour_cell->m_water == m_bot_neighbour_cell->m_volume)
			{
				if (m_bot_neighbour_cell->m_pressure_top <= m_pressure_bot)
				{
					m_bot_neighbour_cell->AddForce((m_pressure_bot - m_bot_neighbour_cell->m_pressure_top), 0, 0, 0);
				}
			}
		}
		else
		{

		}

		if (m_top_neighbour_cell != nullptr)
		{
			if (m_top_neighbour_cell->m_water == m_top_neighbour_cell->m_volume)
			{
				if (m_top_neighbour_cell->m_pressure_bot <= m_pressure_top)
				{
					m_top_neighbour_cell->AddForce(0, 0, (m_pressure_top - m_top_neighbour_cell->m_pressure_bot), 0);
				}
			}
		}

	//}
}