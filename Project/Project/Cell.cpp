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
	m_water = 0 + 0.4 / (double)((rand() % 4) + 1);
	//m_water = (double)1/3;
	
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

float Cell::MaxDensity(double p_pressure)
{
	return 1; //kg/liter
}

void Cell::EarlyUpdate(double deltatime)
{
	m_total_pressure = 0;
	if (m_bot_neighbour_cell != nullptr)
	{
		if (m_bot_neighbour_cell->m_water != m_bot_neighbour_cell->m_volume)
		{
			m_velocity.m_y += (deltatime)*m_water;
		}
		else
		{
			m_bot_neighbour_cell->AddForce(m_water, 0, 0, 0);
			//m_pressure_bot += m_water;
		}
	}
}

void Cell::SendWaterY(Cell *p_cell, int up, int down, double deltatime)
{
	if (p_cell != nullptr)
	{

		if (fabs(m_velocity.m_y) * deltatime <= m_water)
		{
			m_excess_water = p_cell->Receive(fabs(m_velocity.m_y) * deltatime, m_velocity);
			m_water -= fabs(m_velocity.m_y) * deltatime;
		}
		else
		{
			m_excess_water = p_cell->Receive(m_water, m_velocity);
			m_water = 0;
		}

		if (m_excess_water > 0)
		{
			m_water += m_excess_water;
			//p_cell->AddForce(fabs(m_velocity.m_y*m_water)*up, 0, fabs(m_velocity.m_y * m_water)* down, 0);
			m_velocity.m_y = 0;
			//std::cout << std::fixed << std::setprecision(5) << m_velocity.m_y << std::endl;
			//FIXA SÅ ATT MOMENTUM FUNKAR
		}

	}
	else
	{
		m_velocity.m_y = 0;
	}
}

void Cell::SendWaterX(Cell* p_cell, int left, int right, double deltatime)
{
	if (p_cell != nullptr)
	{

		if (fabs(m_velocity.m_x) * deltatime <= m_water)
		{
			m_excess_water = p_cell->Receive(fabs(m_velocity.m_x) * deltatime, m_velocity);
			m_water -= fabs(m_velocity.m_x) * deltatime;
		}
		else
		{
			m_excess_water = p_cell->Receive(m_water, m_velocity);
			m_water = 0;
		}

		if (m_excess_water > 0)
		{
			m_water += m_excess_water;
			//p_cell->AddForce(0, fabs(m_velocity.m_x * m_water)*right, 0, fabs(m_velocity.m_x * m_water)*left);
			m_velocity.m_x = 0;
			//std::cout << std::fixed << std::setprecision(5) << m_velocity.m_y << std::endl;
			//FIXA SÅ ATT MOMENTUM FUNKAR
		}

	}
	else
	{
		m_velocity.m_x = 0;
	}
}

void Cell::Update(double deltatime)
{
	if (m_water > 0)
	{	
		if (m_velocity.m_y > 0)
		{
			SendWaterY(m_bot_neighbour_cell, 0, 1, deltatime);
		}
		else if (m_velocity.m_y < 0)
		{
			SendWaterY(m_top_neighbour_cell, 1, 0, deltatime);
		}

		if (m_velocity.m_x > 0)
		{
			SendWaterX(m_right_neighbour_cell, 0, 1, deltatime);
		}
		else if (m_velocity.m_x > 0)
		{
			SendWaterX(m_left_neighbour_cell, 1, 0, deltatime);
		}
	}
}

void Cell::LateUpdate(double deltatime)
{
	if (true)
	{
		//m_total_pressure = (m_pending_force_top + m_pending_force_right + m_pending_force_bot + m_pending_force_left);
		m_total_pressure = m_pending_force_top;
		if (m_pending_force_right > m_pending_force_top)
		{
			m_total_pressure = m_pending_force_right;
		}
		if (m_pending_force_bot > m_pending_force_right)
		{
			m_total_pressure = m_pending_force_bot;
		}
		if (m_pending_force_left > m_pending_force_bot)
		{
			m_total_pressure = m_pending_force_left;
		}


		if (m_total_pressure > 1000)
		{
			float hello = 0;
		}
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
	else
	{
		m_pending_force_top = 0;
		m_pending_force_right = 0;
		m_pending_force_left = 0;
		m_pending_force_bot = 0;
		m_pressure_top = 0;
		m_pressure_right = 0;
		m_pressure_bot = 0;
		m_pressure_left = 0;
	}


}

void Cell::LateUpdate2(double deltatime)
{
	if (m_total_pressure > 0)
	{
		m_bot_not_full = 0;
		m_right_not_full = 0;
		m_top_not_full = 0;
		m_left_not_full = 0;

		if (m_left_neighbour_cell != nullptr)
		{

			if (m_left_neighbour_cell->m_water == m_left_neighbour_cell->m_volume)
			{

				if (m_left_neighbour_cell->m_pressure_right <= m_pressure_left)
				{
					m_left_neighbour_cell->AddForce(0, (m_pressure_left /*- m_left_neighbour_cell->m_pressure_right*/), 0, 0);
				}
			}
			else if (m_pressure_left > m_left_neighbour_cell->m_pressure_right)
			{
				m_left_not_full = 1;
			}
		}

		if (m_bot_neighbour_cell != nullptr)
		{
			
			if (m_bot_neighbour_cell->m_water == m_bot_neighbour_cell->m_volume)
			{
				
				if (m_bot_neighbour_cell->m_pressure_top <= m_pressure_bot)
				{
					m_bot_neighbour_cell->AddForce(((m_pressure_bot /*- m_bot_neighbour_cell->m_pressure_top*/)), 0, 0, 0);
				}
			}
			else if(m_pressure_bot > m_bot_neighbour_cell->m_pressure_top)
			{
				m_bot_not_full = 1;
			}
		}
		
		
		if (m_right_neighbour_cell != nullptr)
		{
			
			if (m_right_neighbour_cell->m_water == m_right_neighbour_cell->m_volume)
			{
				
				if (m_right_neighbour_cell->m_pressure_left <= m_pressure_right)
				{
					m_right_neighbour_cell->AddForce(0, 0, 0, (m_pressure_right /*- m_right_neighbour_cell->m_pressure_left*/));
				}
			}
			else if (m_pressure_right > m_right_neighbour_cell->m_pressure_left)
			{
				m_right_not_full = 1;
			}
		}

		if (m_top_neighbour_cell != nullptr)
		{
			
			if (m_top_neighbour_cell->m_water == m_top_neighbour_cell->m_volume)
			{
				
				if (m_top_neighbour_cell->m_pressure_bot <= m_pressure_top)
				{
					m_top_neighbour_cell->AddForce(0, 0, (m_pressure_top /*- m_top_neighbour_cell->m_pressure_bot*/), 0);
				}
			}
			else if(m_pressure_top > m_top_neighbour_cell->m_pressure_bot + m_top_neighbour_cell->m_water)
			{
				m_top_not_full = 1;
			}
		}

		
		
		
		
	}
}

void Cell::LateUpdate3(double deltatime)
{
	if (m_total_pressure > 0)
	{
		if ((m_top_not_full + m_right_not_full + m_bot_not_full + m_left_not_full) > 0)
		{
			double flow = m_total_pressure / (m_top_not_full + m_right_not_full + m_bot_not_full + m_left_not_full);

			//std::cout << std::fixed << std::setprecision(10) << m_total_pressure << std::endl;

			Vector2 t_vel;



			if (m_bot_not_full == 1)
			{
				t_vel.m_x = 0;
				t_vel.m_y = flow;

				if (m_water > flow* deltatime)
				{
					m_excess_water = m_bot_neighbour_cell->Receive(flow * deltatime, t_vel);
					m_water -= flow * deltatime;
				}
				else
				{
					m_excess_water = m_bot_neighbour_cell->Receive(m_water/*/hur många sidor, hur många sidor -=1*/, t_vel);
					m_water = 0;
				}

				if (m_excess_water >= 0)
				{
					m_water += m_excess_water;
					//m_bot_neighbour_cell->AddForce(m_pressure_bot + m_water, 0, 0, 0);
					m_velocity.m_y = 0;
				}
			}

			if (m_left_not_full == 1)
			{
				t_vel.m_x = -flow;
				t_vel.m_y = 0;

				if (m_water > flow* deltatime)
				{
					m_excess_water = m_left_neighbour_cell->Receive(flow * deltatime, t_vel);
					m_water -= flow * deltatime;
				}
				else
				{
					m_excess_water = m_left_neighbour_cell->Receive(m_water, t_vel);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_water += m_excess_water;
					//m_left_neighbour_cell->AddForce(0, m_pressure_left, 0, 0);
					m_velocity.m_x = 0;
				}
			}

			if (m_right_not_full == 1)
			{
				t_vel.m_x = flow;
				t_vel.m_y = 0;

				if (m_water > flow* deltatime)
				{
					m_excess_water = m_right_neighbour_cell->Receive(flow * deltatime, t_vel);
					m_water -= flow * deltatime;
				}
				else
				{
					m_excess_water = m_right_neighbour_cell->Receive(m_water, t_vel);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_water += m_excess_water;

					//m_right_neighbour_cell->AddForce(0, 0, 0, m_pressure_right);
					m_velocity.m_x = 0;
				}
			}

			if (m_top_not_full == 1)
			{
				t_vel.m_x = 0;
				t_vel.m_y = -flow;
				if (m_water > flow* deltatime)
				{
					m_excess_water = m_top_neighbour_cell->Receive(flow * deltatime, t_vel);
					m_water -= flow * deltatime;
				}
				else
				{
					m_excess_water = m_top_neighbour_cell->Receive(m_water, t_vel);
					m_water = 0;
				}

				if (m_excess_water > 0)
				{
					m_water += m_excess_water;
					//m_top_neighbour_cell->AddForce(0, 0, m_pressure_top, 0);
					m_velocity.m_y = 0;
				}
			}
		}
	}
}

double Cell::Receive(double p_water, Vector2 p_momentum)
{
	Vector2 t_vel = m_velocity * m_water;
	if (p_momentum.m_y < 0)
	{
		int hey = 10;
	}
	m_water += p_water;
	if (m_water <= m_volume)
	{
		Vector2 t_othervel = p_momentum * p_water;
		//m_velocity = (t_vel + t_othervel) / m_water;
		return 0;
	}
	else
	{
		m_excess_water = m_water - m_volume;
		Vector2 t_othervel = p_momentum * (p_water - m_excess_water);
		
		m_water = m_volume;
		//m_velocity = (t_vel + t_othervel) / m_water;
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