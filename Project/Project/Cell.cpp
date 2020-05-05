#include "Cell.h"
#include <cstdlib>


#include <string>
#include <iostream>
#include <iomanip>

Cell::Cell()
{

}
//Teos10
Cell::~Cell()
{
}

void Cell::Initialize(Cell *p_top_neighbour, Cell *p_right_neighbour, Cell *p_bot_neighbour, Cell *p_left_neighbour)
{
	m_gas = 0 + 0.3 * (double)((rand() % 4));
	//m_gas = 1.225;

	m_gP = 0;
	m_excess_fluid = 0;

	m_tn = p_top_neighbour;
	m_rn = p_right_neighbour;
	m_bn = p_bot_neighbour;
	m_ln = p_left_neighbour;
	
}

void Cell::AirPressure()
{
	m_gP = ((m_gas/M) * R * T)/1;
}

void Cell::AirPressureForce(double deltatime)
{
	m_gQ_down += 20 * deltatime;
	m_gQ_up -= 20 * deltatime;
	//m_gQ_left -= 20 * deltatime;
	//m_gQ_right += 20 * deltatime;

	if (m_rn != nullptr)
	{
		if (m_gas != 0)
		{
			m_gQ_right += ((-1 / (m_gas)) * (m_rn->m_gP - m_gP))*deltatime;
		}
		/*else if (m_rn->m_gas != 0)
		{
			m_gQ_right = (-1 / (m_rn->m_gas)) * (m_rn->m_gP - m_gP);
		}*/
		else m_gQ_right = 0;

		if (m_gQ_right < 0) m_gQ_right = 0;
	}

	if (m_ln != nullptr)
	{
		if (m_gas != 0)
		{
			m_gQ_left += ((-1 / (m_gas)) * (m_ln->m_gP - m_gP))*deltatime;
		}
		else m_gQ_left = 0;

		if (m_gQ_left < 0) m_gQ_left = 0;
	}

	if (m_bn != nullptr)
	{
		if (m_gas != 0)
		{
			m_gQ_down += ((-1 / (m_gas)) * (m_bn->m_gP - m_gP))*deltatime;
		}
		else m_gQ_down = 0;

		if (m_gQ_down < 0) m_gQ_down = 0;
	}

	if (m_tn != nullptr)
	{
		if (m_gas != 0)
		{
			m_gQ_up += ((-1 / (m_gas)) * (m_tn->m_gP - m_gP))*deltatime;
		}
		else m_gQ_up = 0;

		if (m_gQ_up < 0) m_gQ_up = 0;
	}

	
}

void Cell::VelocityUpdate(double deltatime)
{
	if (m_bn != nullptr)
	{
		m_gas -= m_gQ_down * deltatime;
		if (m_gas < 0)
		{
			m_bn->m_gas += (m_gQ_down * deltatime) + m_gas;
			m_gas = 0;

			m_gQ_up = 0;
			m_gQ_right = 0;
			m_gQ_down = 0;
			m_gQ_left = 0;
		}
		else m_bn->m_gas += m_gQ_down * deltatime;
	}

	if (m_ln != nullptr)
	{
		m_gas -= m_gQ_left * deltatime;
		if (m_gas < 0)
		{
			m_ln->m_gas += (m_gQ_left * deltatime) + m_gas;
			m_gas = 0;

			m_gQ_up = 0;
			m_gQ_right = 0;
			m_gQ_down = 0;
			m_gQ_left = 0;
		}
		else m_ln->m_gas += m_gQ_left * deltatime;
	}

	if (m_tn != nullptr)
	{
		m_gas -= m_gQ_up*deltatime;
		if (m_gas < 0)
		{
			m_tn->m_gas += (m_gQ_up * deltatime) + m_gas;
			m_gas = 0;

			m_gQ_up = 0;
			m_gQ_right = 0;
			m_gQ_down = 0;
			m_gQ_left = 0;
		}
		else m_tn->m_gas += m_gQ_up * deltatime;
	}
	
	if (m_rn != nullptr)
	{
		m_gas -= m_gQ_right * deltatime;
		if (m_gas < 0)
		{
			m_rn->m_gas += (m_gQ_right * deltatime) + m_gas;
			m_gas = 0;

			m_gQ_up = 0;
			m_gQ_right = 0;
			m_gQ_down = 0;
			m_gQ_left = 0;
		}
		else m_rn->m_gas += m_gQ_right * deltatime;
	}
	
	
	
	

	m_gQ_up -= 5*m_gQ_up * deltatime;
	m_gQ_right -= 5*m_gQ_right * deltatime;
	m_gQ_down -= 5*m_gQ_down * deltatime;
	m_gQ_left -= 5*m_gQ_left * deltatime;
}

void Cell::LateUpdate2(double deltatime)
{

}

void Cell::LateUpdate3(double deltatime)
{

}

void Cell::Receive(double p_water, Vector2 p_momentum)
{

}

void Cell::AddForce(double p_upforce, double p_rightforce, double p_downforce, double p_leftforce)
{

}

void Cell::SendWaterY(Cell* p_cell, int up, int down, double deltatime)
{

}

void Cell::SendWaterX(Cell* p_cell, int left, int right, double deltatime)
{

}