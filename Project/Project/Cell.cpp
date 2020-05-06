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
	m_gas =0.1*( 0 + 0.3 * (double)((rand() % 4)));
	m_gas2 = 8*(0 + 0.3 * (double)((rand() % 4)));

	M = 29;
	M2 = 100;
	T2 = T;
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
	//ÄNDRING
	m_gP = (((m_gas/*/M*/)) * R * T)+(m_gas2/*/M2*/)*R*T2;
}

void Cell::AirPressureForce(double deltatime, double xacc, double yacc)
{
	//if (m_bn != nullptr)
	{
		m_gQ_down -= (-1) * M * m_gas * deltatime;
		m_gQ_up += (-1) * M *  m_gas * deltatime;
		
		m_gQ_down -= yacc * m_gas * deltatime;
		m_gQ_up += yacc * m_gas * deltatime;

		m_gQ_down2 += 1*M2 * m_gas2 * deltatime;
		m_gQ_up2 -= 1*M2 * m_gas2 * deltatime;

		m_gQ_right += xacc /** M */* m_gas * deltatime;
		m_gQ_left -= xacc /** M*/ * m_gas * deltatime;
		
		m_gQ_right2 += 0 * M2 * m_gas2 * deltatime;
		m_gQ_left2 -= 0 * M2 * m_gas2 * deltatime;

		//m_gQ_down2 += (M2 - M) * deltatime;
		//m_gQ_up2 -= (M2 - M) * deltatime;
	}
	//else
	{
		//m_gQ_down2 += m_gas2 * (m_gas2*M2 - m_gas*M) * deltatime;
		//m_gQ_up2 -= m_gas2 * (m_gas*M2 - m_gas*M) * deltatime;
	}

	//m_gQ_left -= 20 * deltatime;
	//m_gQ_right += 20 * deltatime;
	double t_p = 0;
	if (m_rn != nullptr)
	{
		//1
		{
			if (m_gas != 0)
			{
				m_gQ_right += M*(m_gas + m_gas2) *(m_gas / (m_gas + m_gas2)) * ((-1 / (m_gas*M+m_gas2*M2)) * (m_rn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_right = 0;

			if (m_gQ_right < 0) m_gQ_right = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_right2 += M2 * (m_gas + m_gas2) * (m_gas2 / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_rn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_right2 = 0;

			if (m_gQ_right2 < 0) m_gQ_right2 = 0;
		}
		//END

	}
	else
	{
		m_gQ_right = 0;
		m_gQ_right2 = 0;
	}

	if (m_ln != nullptr)
	{
		//1
		{
			if (m_gas != 0)
			{
				m_gQ_left += M * (m_gas + m_gas2) * (m_gas / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_ln->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_left = 0;

			if (m_gQ_left < 0) m_gQ_left = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_left2 += M2 * (m_gas + m_gas2) * (m_gas2 / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_ln->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_left2 = 0;

			if (m_gQ_left2 < 0) m_gQ_left2 = 0;
		}
		//END
	}
	else
	{
		m_gQ_left = 0;
		m_gQ_left2 = 0;
	}

	if (m_bn != nullptr)
	{
		//1
		{
			if (m_gas != 0)
			{
				m_gQ_down += M * (m_gas + m_gas2) * (m_gas / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_bn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_down = 0;

			if (m_gQ_down < 0) m_gQ_down = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_down2 += M2 * (m_gas + m_gas2) * (m_gas2 / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_bn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_down2 = 0;

			if (m_gQ_down2 < 0) m_gQ_down2 = 0;
		}
		//END
	}
	else
	{
		m_gQ_down = 0;
		m_gQ_down2 = 0;
	}

	if (m_tn != nullptr)
	{
		//1
		{
			if (m_gas != 0)
			{
				m_gQ_up += M * (m_gas + m_gas2) * (m_gas / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_tn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_up = 0;

			if (m_gQ_up < 0) m_gQ_up = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_up2 += M2 * (m_gas+m_gas2) * (m_gas2 / (m_gas + m_gas2)) * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_tn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_up2 = 0;

			if (m_gQ_up2 < 0) m_gQ_up2 = 0;
		}
		//END
	}
	else
	{
		m_gQ_up = 0;
		m_gQ_up2 = 0;
	}

	
}

void Cell::VelocityUpdate(double deltatime)
{
	

	if (m_tn != nullptr)
	{
		//1
		{
			m_gas -= m_gQ_up * deltatime;
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
		//END

		//2
		{
			m_gas2 -= m_gQ_up2 * deltatime;
			if (m_gas2 < 0)
			{
				m_tn->m_gas2 += (m_gQ_up2 * deltatime) + m_gas2;
				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else m_tn->m_gas2 += m_gQ_up2 * deltatime;
		}
		//END
	}
	
	if (m_rn != nullptr)
	{
		//1
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
		//END

		//2
		{
			m_gas2 -= m_gQ_right2 * deltatime;
			if (m_gas2 < 0)
			{
				m_rn->m_gas2 += (m_gQ_right2 * deltatime) + m_gas2;
				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else m_rn->m_gas2 += m_gQ_right2 * deltatime;
		}
		//END
	}
	
	if (m_bn != nullptr)
	{
		//1
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
		//END

		//2
		{
			m_gas2 -= m_gQ_down2 * deltatime;
			if (m_gas2 < 0)
			{
				m_bn->m_gas2 += (m_gQ_down2 * deltatime) + m_gas2;
				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else m_bn->m_gas2 += m_gQ_down2 * deltatime;
		}
		//END
	}

	if (m_ln != nullptr)
	{
		//1
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
		//END

		//2
		{
			m_gas2 -= m_gQ_left2 * deltatime;
			if (m_gas2 < 0)
			{
				m_ln->m_gas2 += (m_gQ_left2 * deltatime) + m_gas2;
				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else m_ln->m_gas2 += m_gQ_left2 * deltatime;
		}
		//END
	}
	
	double fric = 6;
	m_gQ_up2 -= fric * m_gQ_up2 * deltatime;
	m_gQ_right2 -= fric * m_gQ_right2 * deltatime;
	m_gQ_down2 -= fric * m_gQ_down2 * deltatime;
	m_gQ_left2 -= fric * m_gQ_left2 * deltatime;

	m_gQ_up -= fric *m_gQ_up * deltatime;
	m_gQ_right -= fric *m_gQ_right * deltatime;
	m_gQ_down -= fric *m_gQ_down * deltatime;
	m_gQ_left -= fric *m_gQ_left * deltatime;

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