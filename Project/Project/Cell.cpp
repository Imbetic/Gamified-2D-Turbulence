#include "Cell.h"
#include <cstdlib>

#include <math.h>

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
	m_gas =0.5*( 0 + 0.3 * (double)((rand() % 4)));
	m_gas2 = 0.5*(0 + 0.3 * (double)((rand() % 4)));
	//m_gas2 = 0;

	M = 800;
	M2 = 29;
	T2 = T;
	T = 200;
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
	m_gQ_up += m_pgQ_up;
	m_pgQ_up = 0;

	m_gQ_up2 += m_pgQ_up2;
	m_pgQ_up2 = 0;

	m_gQ_right += m_pgQ_right;
	m_pgQ_right = 0;

	m_gQ_right2 += m_pgQ_right2;
	m_pgQ_right2 = 0;

	m_gQ_down += m_pgQ_down;
	m_pgQ_down = 0;

	m_gQ_down2 += m_pgQ_down2;
	m_pgQ_down2 = 0;

	m_gQ_left += m_pgQ_left;
	m_pgQ_left = 0;

	m_gQ_left2 += m_pgQ_left2;
	m_pgQ_left2 = 0;


	m_gas += m_pgas;
	m_gas2 += m_pgas2;

	m_pgas = 0;
	m_pgas2 = 0;

	m_gP = (((m_gas/*/M*/)) * R * T)+(m_gas2/*/M2*/)*R*T2;
}

void Cell::AirPressureForce(double deltatime, double xacc, double yacc)
{
	
	//if (m_bn != nullptr)
	{
		
		
		m_gQ_down2 -= M2 * yacc * m_gas2 * deltatime;
		m_gQ_up2 += M2 * yacc * m_gas2 * deltatime;
		m_gQ_right2 += M2 * xacc * m_gas2 * deltatime;
		m_gQ_left2 -= M2 * xacc * m_gas2 * deltatime;

		/*m_gQ_down2 -= M2 * yacc * m_gas2 * deltatime;
		m_gQ_up2 += M2 * yacc * m_gas2 * deltatime;
		m_gQ_right2 += M2 * xacc * m_gas2 * deltatime;
		m_gQ_left2 -= M2 * xacc * m_gas2 * deltatime;*/

		m_gQ_down -= (-1) * M * m_gas * deltatime;
		m_gQ_up += (-1) * M *  m_gas * deltatime;

		m_gQ_down2 += 1*M2 * m_gas2 * deltatime;
		m_gQ_up2 -= 1*M2 * m_gas2 * deltatime;

		//m_gQ_right2 += 1 * M2 * m_gas2 * deltatime;
		//m_gQ_left2 -= 1 * M2 * m_gas2 * deltatime;

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
	double friction = 0.99;

	m_gQ_down = m_gQ_down/** m_gQ_down*/ * friction /** deltatime*/;
	m_gQ_up = m_gQ_up/** m_gQ_up*/ * friction/* * deltatime*/;
	m_gQ_right = m_gQ_right/* * m_gQ_right*/ * friction /** deltatime*/;
	m_gQ_left = m_gQ_left/* * m_gQ_left*/ * friction /** deltatime*/;

	m_gQ_down2 = m_gQ_down2/* * m_gQ_down2*/ * friction /** deltatime*/;
	m_gQ_up2 = m_gQ_up2 /** m_gQ_up2*/ * friction /** deltatime*/;
	m_gQ_right2 = m_gQ_right2/**m_gQ_right2*/ * friction/* * deltatime*/;
	m_gQ_left2 = m_gQ_left2/**m_gQ_left2*/ * friction /** deltatime*/;
	

	if (m_rn != nullptr)
	{
		//gas1
		//if (m_gas != 0 && m_gQ_right > 0)
		{
			m_gas -= m_gQ_right * deltatime;
			if (m_gas < 0)
			{
				m_rn->m_pgas += (m_gQ_right * deltatime) + m_gas;

				m_rn->m_pgQ_right += ((m_gQ_right * deltatime) + m_gas) * GasFraction(M * (((m_gQ_right * deltatime) + m_gas) + m_rn->m_gas), M2 * m_rn->m_gas2);
				m_rn->m_pgQ_right2 += (M / M2) * ((m_gQ_right * deltatime) + m_gas) * GasFraction(M2 * m_rn->m_gas2, M * (((m_gQ_right * deltatime) + m_gas) + m_rn->m_gas));

				m_gas = 0;

				m_gQ_up = 0;
				m_gQ_right = 0;
				m_gQ_down = 0;
				m_gQ_left = 0;
			}
			else
			{
				m_rn->m_pgas += m_gQ_right * deltatime;
				m_rn->m_pgQ_right += ((m_gQ_right * deltatime)) * GasFraction(M * (((m_gQ_right * deltatime)) + m_rn->m_gas), M2 * m_rn->m_gas2);
				m_rn->m_pgQ_right2 += (M / M2) * ((m_gQ_right * deltatime)) * GasFraction(M2 * m_rn->m_gas2, M * (((m_gQ_right * deltatime)) + m_rn->m_gas));
			}
		}
		//END

		//2
		//if (m_gas2 != 0 && m_gQ_right2 > 0)
		{
			m_gas2 -= m_gQ_right2 * deltatime;
			if (m_gas2 < 0)
			{
				m_rn->m_pgas2 += (m_gQ_right2 * deltatime) + m_gas2;

				m_rn->m_pgQ_right2 += ((m_gQ_right2 * deltatime) + m_gas2) * GasFraction(M2 * (((m_gQ_right2 * deltatime) + m_gas2) + m_rn->m_gas2), M * m_rn->m_gas);
				m_rn->m_pgQ_right += (M2 / M) * ((m_gQ_right2 * deltatime) + m_gas2) * GasFraction(M * m_rn->m_gas, M2 * (((m_gQ_right2 * deltatime) + m_gas2) + m_rn->m_gas2));

				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else
			{
				m_rn->m_pgas2 += m_gQ_right2 * deltatime;
				
				m_rn->m_pgQ_right2 += ((m_gQ_right2 * deltatime)) * GasFraction(M2 * (((m_gQ_right2 * deltatime)) + m_rn->m_gas2), M * m_rn->m_gas);
				m_rn->m_pgQ_right += (M2 / M) * ((m_gQ_right2 * deltatime)) * GasFraction(M * m_rn->m_gas, M2 * (((m_gQ_right2 * deltatime)) + m_rn->m_gas2));
			}
		}
		//END
	}


	if (m_tn != nullptr)
	{
		//gas1
		//if (m_gas != 0 && m_gQ_up > 0)
		{
			m_gas -= m_gQ_up * deltatime;
			if (m_gas < 0)
			{
				m_tn->m_pgas += (m_gQ_up * deltatime) + m_gas;
				
				m_tn->m_pgQ_up += ((m_gQ_up * deltatime) + m_gas) * GasFraction(M*(((m_gQ_up * deltatime) + m_gas)+m_tn->m_gas), M2*m_tn->m_gas2);
				m_tn->m_pgQ_up2 += (M / M2) * ((m_gQ_up * deltatime) + m_gas) * GasFraction(M2*m_tn->m_gas2, M*(((m_gQ_up * deltatime) + m_gas) + m_tn->m_gas));
				

				m_gas = 0;

				m_gQ_up = 0;
				m_gQ_right = 0;
				m_gQ_down = 0;
				m_gQ_left = 0;
			}
			else
			{
				m_tn->m_pgas += m_gQ_up * deltatime;

				m_tn->m_pgQ_up += ((m_gQ_up * deltatime)) * GasFraction(M * (((m_gQ_up * deltatime)) + m_tn->m_gas), M2 * m_tn->m_gas2);
				m_tn->m_pgQ_up2 += (M/M2)*((m_gQ_up * deltatime)) * GasFraction(M2 * m_tn->m_gas2, M * (((m_gQ_up * deltatime)) + m_tn->m_gas));
			}
		}
		//END

		//gas2
		//if (m_gas != 0 && m_gQ_up2 > 0)
		{
			m_gas2 -= m_gQ_up2 * deltatime;
			if (m_gas2 < 0)
			{
				m_tn->m_pgas2 += (m_gQ_up2 * deltatime) + m_gas2;

				m_tn->m_pgQ_up2 += ((m_gQ_up2 * deltatime) + m_gas2) * GasFraction(M2 * (((m_gQ_up2 * deltatime) + m_gas2) + m_tn->m_gas2), M * m_tn->m_gas);
				m_tn->m_pgQ_up += (M2/M)*((m_gQ_up2 * deltatime) + m_gas2) * GasFraction(M * m_tn->m_gas, M2 * (((m_gQ_up2 * deltatime) + m_gas2) + m_tn->m_gas2));

				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else
			{
				m_tn->m_pgQ_up2 += ((m_gQ_up2 * deltatime)) * GasFraction(M2 * (((m_gQ_up2 * deltatime)) + m_tn->m_gas2), M * m_tn->m_gas);
				m_tn->m_pgQ_up += (M2 / M)*((m_gQ_up2 * deltatime)) * GasFraction(M * m_tn->m_gas, M2 * (((m_gQ_up2 * deltatime)) + m_tn->m_gas2));

				m_tn->m_pgas2 += m_gQ_up2 * deltatime;
			}

		}
		//END
	}
	

	
	
	if (m_bn != nullptr)
	{
		//1
		//if (m_gas != 0 && m_gQ_down > 0)
		{
			m_gas -= m_gQ_down * deltatime;
			if (m_gas < 0)
			{
				m_bn->m_pgas += (m_gQ_down * deltatime) + m_gas;

				m_bn->m_pgQ_down += ((m_gQ_down * deltatime) + m_gas) * GasFraction(M * (((m_gQ_down * deltatime) + m_gas) + m_bn->m_gas), M2 * m_bn->m_gas2);
				m_bn->m_pgQ_down2 += (M / M2) * ((m_gQ_down * deltatime) + m_gas) * GasFraction(M2 * m_bn->m_gas2, M * (((m_gQ_down * deltatime) + m_gas) + m_bn->m_gas));

				m_gas = 0;

				m_gQ_up = 0;
				m_gQ_right = 0;
				m_gQ_down = 0;
				m_gQ_left = 0;
			}
			else
			{
				m_bn->m_pgas += m_gQ_down * deltatime;
				m_bn->m_pgQ_down += ((m_gQ_down * deltatime)) * GasFraction(M * (((m_gQ_down * deltatime)) + m_bn->m_gas), M2 * m_bn->m_gas2);
				m_bn->m_pgQ_down2 += (M / M2) * ((m_gQ_down * deltatime)) * GasFraction(M2 * m_bn->m_gas2, M * (((m_gQ_down * deltatime)) + m_bn->m_gas));
			}
		}
		//END

		//2
		//if (m_gas != 0 && m_gQ_down2 > 0)
		{
			m_gas2 -= m_gQ_down2 * deltatime;
			if (m_gas2 < 0)
			{
				m_bn->m_pgas2 += (m_gQ_down2 * deltatime) + m_gas2;

				m_bn->m_pgQ_down2 += ((m_gQ_down2 * deltatime) + m_gas2) * GasFraction(M2 * (((m_gQ_down2 * deltatime) + m_gas2) + m_bn->m_gas2), M * m_bn->m_gas);
				m_bn->m_pgQ_down += (M2 / M) * ((m_gQ_down2 * deltatime) + m_gas2) * GasFraction(M * m_bn->m_gas, M2 * (((m_gQ_down2 * deltatime) + m_gas2) + m_bn->m_gas2));

				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else
			{
				m_bn->m_pgas2 += m_gQ_down2 * deltatime;

				m_bn->m_pgQ_down2 += ((m_gQ_down2 * deltatime)) * GasFraction(M2 * (((m_gQ_down2 * deltatime)) + m_bn->m_gas2), M * m_bn->m_gas);
				m_bn->m_pgQ_down += (M2 / M) * ((m_gQ_down2 * deltatime)) * GasFraction(M * m_bn->m_gas, M2 * (((m_gQ_down2 * deltatime)) + m_bn->m_gas2));
			}
		}
		//END
	}

	if (m_ln != nullptr)
	{
		//1
		//if (m_gas != 0 && m_gQ_left > 0)
		{
			m_gas -= m_gQ_left * deltatime;
			if (m_gas < 0)
			{
				m_ln->m_pgas += (m_gQ_left * deltatime) + m_gas;

				m_ln->m_pgQ_left += ((m_gQ_left * deltatime) + m_gas) * GasFraction(M * (((m_gQ_left * deltatime) + m_gas) + m_ln->m_gas), M2 * m_ln->m_gas2);
				m_ln->m_pgQ_left2 += (M / M2) * ((m_gQ_left * deltatime) + m_gas) * GasFraction(M2 * m_ln->m_gas2, M * (((m_gQ_left * deltatime) + m_gas) + m_ln->m_gas));

				m_gas = 0;

				m_gQ_up = 0;
				m_gQ_right = 0;
				m_gQ_down = 0;
				m_gQ_left = 0;
			}
			else
			{
				m_ln->m_pgas += m_gQ_left * deltatime;

				m_ln->m_pgQ_left += ((m_gQ_left * deltatime)) * GasFraction(M * (((m_gQ_left * deltatime)) + m_ln->m_gas), M2 * m_ln->m_gas2);
				m_ln->m_pgQ_left2 += (M / M2) * ((m_gQ_left * deltatime)) * GasFraction(M2 * m_ln->m_gas2, M * (((m_gQ_left * deltatime)) + m_ln->m_gas));
			}
		}
		//END

		//2
		//if (m_gas != 0 && m_gQ_left2 > 0)
		{
			m_gas2 -= m_gQ_left2 * deltatime;
			if (m_gas2 < 0)
			{
				m_ln->m_pgas2 += (m_gQ_left2 * deltatime) + m_gas2;

				m_ln->m_pgQ_left2 += ((m_gQ_left2 * deltatime) + m_gas2) * GasFraction(M2 * (((m_gQ_left2 * deltatime) + m_gas2) + m_ln->m_gas2), M * m_ln->m_gas);
				m_ln->m_pgQ_left += (M2 / M) * ((m_gQ_left2 * deltatime) + m_gas2) * GasFraction(M * m_ln->m_gas, M2 * (((m_gQ_left2 * deltatime) + m_gas2) + m_ln->m_gas2));

				m_gas2 = 0;

				m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;
			}
			else
			{
				m_ln->m_pgas2 += m_gQ_left2 * deltatime;

				m_ln->m_pgQ_left2 += ((m_gQ_left2 * deltatime)) * GasFraction(M2 * (((m_gQ_left2 * deltatime)) + m_ln->m_gas2), M * m_ln->m_gas);
				m_ln->m_pgQ_left += (M2 / M) * ((m_gQ_left2 * deltatime)) * GasFraction(M * m_ln->m_gas, M2 * (((m_gQ_left2 * deltatime)) + m_ln->m_gas2));
			}
		}
		//END
	}
	
	
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

double Cell::GasFraction(double gasM1, double gasM2)
{
	if (gasM1 == 0 && gasM2 == 0)
	{
		return 0;
	}
	return gasM1 / (gasM1+gasM2);
}