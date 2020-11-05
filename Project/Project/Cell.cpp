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
	m_gas =0.03*( 0 + 0.3 * (double)((rand() % 4)));
	//m_gas2 = 10*(0 + 0.3 * (double)((rand() % 4)));
	//m_gas2 = 0;

	M = 10;
	M2 = 1;
	T2 = T;
	//T = 200;
	//m_gas = 1.225;
	//R = 4;

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
	/*m_gQ_up += m_pgQ_up;
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
	m_pgQ_left2 = 0;*/


	m_gas += m_pgas;

	if (m_gas <= 0)
	{
		m_gQ_up = 0;
		m_gQ_down = 0;
		m_gQ_right = 0;
		m_gQ_left = 0;

	}

	m_gas2 += m_pgas2;

	if (m_gas2 <= 0)
	{
		m_gQ_up2 = 0;
		m_gQ_down2 = 0;
		m_gQ_right2 = 0;
		m_gQ_left2 = 0;

	}

	m_pgas = 0;
	m_pgas2 = 0;

	m_gP = (((m_gas/*/M*/)) * R * T)+(m_gas2/*/M2*/)*R*T2;
}

void Cell::MovePlayer1(double dt, double xacc, double yacc)
{
	m_gQ_down -= 50*yacc * m_gas * dt;
	m_gQ_up += 50 * yacc * m_gas * dt;
	m_gQ_right -= 50 * xacc * m_gas * dt;
	m_gQ_left += 50 * xacc * m_gas * dt;


	m_gQ_down *= 0.999;
	m_gQ_up *= 0.999;
	m_gQ_left *= 0.999;
	m_gQ_right *= 0.999;
	/*m_gQ_down2 -= M2 * yacc * m_gas2 * dt;
	m_gQ_up2 += M2 * yacc * m_gas2 * dt;
	m_gQ_right2 -= M2 * xacc * m_gas2 * dt;
	m_gQ_left2 += M2 * xacc * m_gas2 * dt;*/


}

void Cell::MovePlayer2(double dt, double xacc, double yacc)
{
	m_gQ_down2 -= 30000 * yacc * m_gas2 * dt;
	m_gQ_up2 += 30000 * yacc * m_gas2 * dt;
	m_gQ_right2 -= 30000 * xacc * m_gas2 * dt;
	m_gQ_left2 += 30000 * xacc * m_gas2 * dt;
}

void Cell::Gravity(double xacc, double yacc)
{
	m_gQ_down -= 3*(yacc) * M * m_gas;
	m_gQ_up += 3 * (yacc) * M * m_gas;
	m_gQ_right += 3 * (xacc)*M * m_gas;
	m_gQ_left -= 3 * (xacc)*M * m_gas;

	m_gQ_down2 -= 3 * (yacc)*M2 * m_gas2;
	m_gQ_up2 += 3 * (yacc)*M2 * m_gas2;
	m_gQ_right2 += 3 * (xacc)*M2 * m_gas2;
	m_gQ_left2 -= 3 * (xacc)*M2 * m_gas2;

}

void Cell::AirPressureForce(double deltatime)
{
	//if (GetTotMass() != 0)
	//{
	//	
	//	//m_pgQ_right /= GetTotMass();
	//	m_pgQ_right *= 1;
	//	m_pgQ_up *= 1;

	//	if (m_ln != nullptr && m_rn != nullptr)
	//	{
	//		m_gQ_right += m_pgQ_right * GasFraction(m_gas, m_gas2) / GetMass1();
	//		m_gQ_left -= m_pgQ_right * GasFraction(m_gas, m_gas2) / GetMass1();

	//		m_gQ_right2 += m_pgQ_right * GasFraction(m_gas2, m_gas) / GetMass2();
	//		m_gQ_left2 -= m_pgQ_right * GasFraction(m_gas2, m_gas) / GetMass2();
	//	}
	//	if (m_tn != nullptr && m_bn != nullptr)
	//	{
	//		//m_pgQ_up /= GetTotMass();
	//		m_gQ_up += m_pgQ_up * GasFraction(m_gas, m_gas2) / GetMass1();
	//		m_gQ_down -= m_pgQ_up * GasFraction(m_gas, m_gas2) / GetMass1();

	//		m_gQ_up2 += m_pgQ_up * GasFraction(m_gas2, m_gas) / GetMass2();
	//		m_gQ_down2 -= m_pgQ_up * GasFraction(m_gas2, m_gas) / GetMass2();
	//	}
	//}

	m_pgQ_right = 0;
	m_pgQ_left = 0;

	double t_p = 0;
	if (m_rn != nullptr)
	{
		//1
		{
			if (m_gas != 0)
			{
				m_gQ_right += M*(m_gas) /**(m_gas / (m_gas + m_gas2))*/ * ((-1 / (m_gas*M+m_gas2*M2)) * (m_rn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_right = 0;

			if (m_gQ_right < 0) m_gQ_right = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_right2 += M2 * (m_gas2) /** (m_gas2 / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_rn->m_gP - m_gP)) * deltatime;
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
				m_gQ_left += M * (m_gas) /** (m_gas / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_ln->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_left = 0;

			if (m_gQ_left < 0) m_gQ_left = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_left2 += M2 * (m_gas2) /** (m_gas2 / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_ln->m_gP - m_gP)) * deltatime;
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
				m_gQ_down += M * (m_gas) /** (m_gas / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_bn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_down = 0;

			if (m_gQ_down < 0) m_gQ_down = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_down2 += M2 * (m_gas2) /** (m_gas2 / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_bn->m_gP - m_gP)) * deltatime;
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
				m_gQ_up += M * (m_gas) /** (m_gas / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_tn->m_gP - m_gP)) * deltatime;
			}
			else m_gQ_up = 0;

			if (m_gQ_up < 0) m_gQ_up = 0;
		}
		//END

		//2
		{
			if (m_gas2 != 0)
			{
				m_gQ_up2 += M2 * (m_gas2) /** (m_gas2 / (m_gas + m_gas2))*/ * ((-1 / (m_gas * M + m_gas2 * M2)) * (m_tn->m_gP - m_gP)) * deltatime;
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
	friction = 0.8;

	//friction2 = 0.999;

	/*m_gQ_down = ((m_gQ_down) / (1 + friction * m_gQ_down));
	m_gQ_up = ((m_gQ_up) / (1 + friction * m_gQ_up));
	m_gQ_left = (m_gQ_left) / (1 + friction * m_gQ_left);
	m_gQ_right =(m_gQ_right) / (1 + friction * m_gQ_right);

	m_gQ_down2 = (m_gQ_down2) / (1 + friction * m_gQ_down2);
	m_gQ_up2 = (m_gQ_up2) / (1 + friction * m_gQ_up2);
	m_gQ_left2 = (m_gQ_left2) / (1 + friction * m_gQ_left2);
	m_gQ_right2 = (m_gQ_right2) / (1 + friction * m_gQ_right2);*/

	//double fric1 = m_gQ_down * pow(friction, deltatime) - m_gQ_down;

	//m_gQ_down -= (m_gQ_down * (-powf(friction, deltatime )+1)) / (M / 100);
	//m_gQ_up -= (m_gQ_up * (-powf(friction, deltatime /*/ (M / 100)*/)+1)) / (M / 100);
	//m_gQ_right -= (m_gQ_right * (-powf(friction, deltatime /*/ (M / 100)*/)+1)) / (M / 100);
	//m_gQ_left -= (m_gQ_left * (-powf(friction, deltatime /*/ (M / 100)*/)+1)) / (M / 100);

	//
	//m_gQ_down2 -= (m_gQ_down2 * (-powf(friction, deltatime /*/ (M2 / 100)*/)+1)) / (M2 / 100);
	//m_gQ_up2 -= (m_gQ_up2 * (-powf(friction, deltatime /*/ (M2 / 100)*/)+1)) / (M2 / 100);
	//m_gQ_right2 -= (m_gQ_right2 * (-powf(friction, deltatime/* / (M2 / 100)*/)+1)) / (M2 / 100);
	//m_gQ_left2 -= (m_gQ_left2 * (-powf(friction, deltatime /*/ (M2 / 100)*/)+1)) / (M2 / 100);

	

	m_gQ_down = (m_gQ_down * (powf(friction, deltatime / (M / 100))));
	m_gQ_up = (m_gQ_up * (powf(friction, deltatime / (M / 100))));
	m_gQ_right = (m_gQ_right * (powf(friction, deltatime / (M / 100))));
	m_gQ_left = (m_gQ_left * (powf(friction, deltatime / (M / 100))));


	m_gQ_down2 = (m_gQ_down2 * (powf(friction, deltatime / (M2 / 100))));
	m_gQ_up2 = (m_gQ_up2 * (powf(friction, deltatime / (M2 / 100))));
	m_gQ_right2 = (m_gQ_right2 * (powf(friction, deltatime / (M2 / 100))));
	m_gQ_left2 = (m_gQ_left2 * (powf(friction, deltatime / (M2 / 100))));
	
	if (m_bn != nullptr)
	{
		//1
		//if (m_gas != 0 && m_gQ_down > 0)
		{
			if (m_gQ_down > 0)
			{
				m_gas -= m_gQ_down * deltatime;
				if (m_gas < 0)
				{
					t_flow = (m_gQ_down * deltatime) + m_gas;
					m_bn->m_pgas += t_flow;
					//t_flow *= M;
					m_bn->m_pgQ_up -= m_gQ_down * t_flow * M;
					/*	m_bn->m_pgQ_down += friction2 * GasFraction(t_flow + m_bn->GetMass1(), m_bn->GetMass2()) * m_gQ_down * t_flow / (t_flow + m_bn->GetMass1());
						m_bn->m_pgQ_down2 += friction2 * GasFraction(m_bn->GetMass2(), t_flow + m_bn->GetMass1()) * (M / M2) * m_gQ_down * t_flow / (t_flow + m_bn->GetMass2());*/

					m_gas = 0;

					/*m_gQ_up = 0;
					m_gQ_right = 0;
					m_gQ_down = 0;
					m_gQ_left = 0;*/
				}
				else
				{
					t_flow = m_gQ_down * deltatime;
					m_bn->m_pgas += t_flow;
					//t_flow *= M;
					m_bn->m_pgQ_up -= m_gQ_down * t_flow * M;
					/*m_bn->m_pgQ_down += friction2 * GasFraction(t_flow + m_bn->GetMass1(), m_bn->GetMass2()) * m_gQ_down * t_flow / (t_flow + m_bn->GetMass1());
					m_bn->m_pgQ_down2 += friction2 * GasFraction(m_bn->GetMass2(), t_flow + m_bn->GetMass1()) * (M / M2) * m_gQ_down * t_flow / (t_flow + m_bn->GetMass2());*/
				}
			}
		}
		//END

		//2
		//if (m_gas != 0 && m_gQ_down2 > 0)
		{
			if (m_gQ_down2 > 0)
			{
				m_gas2 -= m_gQ_down2 * deltatime;
				if (m_gas2 < 0)
				{
					t_flow = (m_gQ_down2 * deltatime) + m_gas2;
					m_bn->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_bn->m_pgQ_up -= m_gQ_down2 * t_flow * M2;
					/*m_bn->m_pgQ_down2 += friction2 * GasFraction(t_flow + m_bn->GetMass2(), m_bn->GetMass1()) * m_gQ_down2 * t_flow / (t_flow + m_bn->GetMass2());
					m_bn->m_pgQ_down += friction2 * GasFraction(m_bn->GetMass1(), t_flow + m_bn->GetMass2()) * (M2 / M) * m_gQ_down2 * t_flow / (t_flow + m_bn->GetMass1());*/

					m_gas2 = 0;

					/*		m_gQ_up2 = 0;
							m_gQ_right2 = 0;
							m_gQ_down2 = 0;
							m_gQ_left2 = 0;*/
				}
				else
				{
					t_flow = m_gQ_down2 * deltatime;
					m_bn->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_bn->m_pgQ_up -= m_gQ_down2 * t_flow * M2;
					/*m_bn->m_pgQ_down2 += friction2 * GasFraction(t_flow + m_bn->GetMass2(), m_bn->GetMass1()) * m_gQ_down2 * t_flow / (t_flow + m_bn->GetMass2());
					m_bn->m_pgQ_down += friction2 * GasFraction(m_bn->GetMass1(), t_flow + m_bn->GetMass2()) * (M2 / M) * m_gQ_down2 * t_flow / (t_flow + m_bn->GetMass1());*/
				}
			}
		}
		//END
	}
	
	if (m_rn != nullptr)
	{
		//gas1
		{
			if (m_gQ_right > 0)
			{
				m_gas -= m_gQ_right * deltatime;

				if (m_gas < 0)
				{
					t_flow = (m_gQ_right * deltatime) + m_gas;
					m_rn->m_pgas += t_flow;
					//t_flow *= M;
					m_rn->m_pgQ_right += m_gQ_right * t_flow * M;
					/*m_rn->m_pgQ_right += friction2 * GasFraction(t_flow + m_rn->GetMass1(), m_rn->GetMass2()) * m_gQ_right * t_flow / (t_flow + m_rn->GetMass1());
					m_rn->m_pgQ_right2 += friction2 * GasFraction(m_rn->GetMass2(), t_flow + m_rn->GetMass1()) * (M / M2) * m_gQ_right * t_flow / (t_flow + m_rn->GetMass2());*/


					m_gas = 0;

					/*m_gQ_up = 0;
					m_gQ_right = 0;
					m_gQ_down = 0;
					m_gQ_left = 0;*/
				}
				else
				{
					t_flow = (m_gQ_right * deltatime);

					m_rn->m_pgas += t_flow;
					//t_flow *= M;
					m_rn->m_pgQ_right += m_gQ_right * t_flow * M;
					/*m_rn->m_pgQ_right += friction2 * GasFraction(t_flow + m_rn->GetMass1(), m_rn->GetMass2()) * m_gQ_right * t_flow / (t_flow + m_rn->GetMass1());
					m_rn->m_pgQ_right2 += friction2 * GasFraction(m_rn->GetMass2(), t_flow + m_rn->GetMass1()) * (M / M2) * m_gQ_right * t_flow / (t_flow + m_rn->GetMass2());*/

				}
			}
		}
		//END

		//2
		{
			if (m_gQ_right2 > 0)
			{
				m_gas2 -= m_gQ_right2 * deltatime;
				if (m_gas2 < 0)
				{
					t_flow = (m_gQ_right2 * deltatime) + m_gas2;
					m_rn->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_rn->m_pgQ_right += m_gQ_right2 * t_flow * M2;
					/*m_rn->m_pgQ_right2 += friction2 * GasFraction(t_flow + m_rn->GetMass2(), m_rn->GetMass1()) * m_gQ_right2 * t_flow / (t_flow + m_rn->GetMass2());
					m_rn->m_pgQ_right += friction2 * GasFraction(m_rn->GetMass1(), t_flow + m_rn->GetMass2()) * (M2 / M) * m_gQ_right2 * t_flow / (t_flow + m_rn->GetMass1());*/

					m_gas2 = 0;

					/*m_gQ_up2 = 0;
					m_gQ_right2 = 0;
					m_gQ_down2 = 0;
					m_gQ_left2 = 0;*/
				}
				else
				{
					t_flow = m_gQ_right2 * deltatime;
					m_rn->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_rn->m_pgQ_right += m_gQ_right2 * t_flow * M2;
					/*m_rn->m_pgQ_right2 += friction2 * GasFraction(t_flow + m_rn->GetMass2(), m_rn->GetMass1()) * m_gQ_right2 * t_flow / (t_flow + m_rn->GetMass2());
					m_rn->m_pgQ_right += friction2 * GasFraction(m_rn->GetMass1(), t_flow + m_rn->GetMass2()) * (M2 / M) * m_gQ_right2 * t_flow / (t_flow + m_rn->GetMass1());*/
				}
			}
		}
		//END
	}
	
	if (m_ln != nullptr)
	{
		//1
		//if (m_gas != 0 && m_gQ_left > 0)
		{
			if (m_gQ_left > 0)
			{
				m_gas -= m_gQ_left * deltatime;
				if (m_gas < 0)
				{
					t_flow = (m_gQ_left * deltatime) + m_gas;
					m_ln->m_pgas += t_flow;
					//t_flow *= M;

					m_ln->m_pgQ_right -= m_gQ_left * t_flow * M;

					/*m_ln->m_pgQ_left += friction2 * GasFraction(t_flow + m_ln->GetMass1(), m_ln->GetMass2()) * m_gQ_left * t_flow / (t_flow + m_ln->GetMass1());
					m_ln->m_pgQ_left2 += friction2 * GasFraction(m_ln->GetMass2(), t_flow + m_ln->GetMass1()) * (M / M2) * m_gQ_left * t_flow / (t_flow + m_ln->GetMass2());*/

					m_gas = 0;

					/*	m_gQ_up = 0;
						m_gQ_right = 0;
						m_gQ_down = 0;
						m_gQ_left = 0;*/
				}
				else
				{
					t_flow = m_gQ_left * deltatime;
					m_ln->m_pgas += t_flow;
					//t_flow *= M;

					m_ln->m_pgQ_right -= m_gQ_left * t_flow * M;

					/*m_ln->m_pgQ_left += friction2 * GasFraction(t_flow + m_ln->GetMass1(), m_ln->GetMass2()) * m_gQ_left * t_flow / (t_flow + m_ln->GetMass1());
					m_ln->m_pgQ_left2 += friction2 * GasFraction(m_ln->GetMass2(), t_flow + m_ln->GetMass1()) * (M / M2) * m_gQ_left * t_flow / (t_flow + m_ln->GetMass2());*/
				}
			}
		}
		//END

		//2
		//if (m_gas != 0 && m_gQ_left2 > 0)
		{
			if (m_gQ_left2 > 0)
			{
				m_gas2 -= m_gQ_left2 * deltatime;
				if (m_gas2 < 0)
				{
					t_flow = (m_gQ_left2 * deltatime) + m_gas2;
					m_ln->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_ln->m_pgQ_right -= m_gQ_left2 * t_flow * M2;
					/*m_ln->m_pgQ_left2 += friction2 * GasFraction(t_flow + m_ln->GetMass2(), m_ln->GetMass1()) * m_gQ_left2 * t_flow / (t_flow + m_ln->GetMass2());
					m_ln->m_pgQ_down += friction2 * GasFraction(m_ln->GetMass1(), t_flow + m_ln->GetMass2()) * (M2 / M) * m_gQ_left2 * t_flow / (t_flow + m_ln->GetMass1());*/

					m_gas2 = 0;

					//m_gQ_up2 = 0;
					//m_gQ_right2 = 0;
					//m_gQ_down2 = 0;
					//m_gQ_left2 = 0;
				}
				else
				{
					t_flow = m_gQ_left2 * deltatime;
					m_ln->m_pgas2 += t_flow;
					//t_flow *= M2;
					m_ln->m_pgQ_right -= m_gQ_left2 * t_flow * M2;
					/*m_ln->m_pgQ_left2 += friction2 * GasFraction(t_flow + m_ln->GetMass2(), m_ln->GetMass1()) * m_gQ_left2 * t_flow / (t_flow + m_ln->GetMass2());
					m_ln->m_pgQ_down += friction2 * GasFraction(m_ln->GetMass1(), t_flow + m_ln->GetMass2()) * (M2 / M) * m_gQ_left2 * t_flow / (t_flow + m_ln->GetMass1());*/
				}
			}
		}
		//END
	}

	if (m_tn != nullptr)
	{
		//gas1

		{
			if(m_gQ_up>0)
			{
				m_gas -= m_gQ_up * deltatime;

				if (m_gas < 0)
				{
					t_flow = (m_gQ_up * deltatime) + m_gas;
					m_tn->m_pgas += t_flow;
					//t_flow *= M;
					m_tn->m_pgQ_up += m_gQ_up * t_flow * M;
					/*m_tn->m_pgQ_up += friction2 *GasFraction(t_flow + m_tn->GetMass1(), m_tn->GetMass2()) * m_gQ_up * t_flow / (t_flow + m_tn->GetMass1());
					m_tn->m_pgQ_up2 += friction2 * GasFraction(m_tn->GetMass2(), t_flow + m_tn->GetMass1()) * (M / M2) * m_gQ_up * t_flow / (t_flow + m_tn->GetMass2());*/


					m_gas = 0;

					/*m_gQ_up = 0;
					m_gQ_right = 0;
					m_gQ_down = 0;
					m_gQ_left = 0;*/
				}
				else
				{
					t_flow = m_gQ_up * deltatime;
					m_tn->m_pgas += t_flow;
					//t_flow *= M;
					m_tn->m_pgQ_up += m_gQ_up * t_flow * M;
					/*m_tn->m_pgQ_up += friction2 * GasFraction(t_flow + m_tn->GetMass1(), m_tn->GetMass2()) * m_gQ_up * t_flow / (t_flow + m_tn->GetMass1());
					m_tn->m_pgQ_up2 += friction2 * GasFraction(m_tn->GetMass2(), t_flow + m_tn->GetMass1()) * (M / M2) * m_gQ_up * t_flow / (t_flow + m_tn->GetMass2());*/
				}
			}
		}
		//END

		//gas2
		if (m_gQ_up2 > 0)
		{
			m_gas2 -= m_gQ_up2 * deltatime;
			if (m_gas2 < 0)
			{
				t_flow = (m_gQ_up2 * deltatime) + m_gas2;
				m_tn->m_pgas2 += t_flow;
				//t_flow *= M2;
				m_tn->m_pgQ_up += m_gQ_up2 * t_flow * M2;
				/*m_tn->m_pgQ_up2 += friction2 * GasFraction(t_flow + m_tn->GetMass2(), m_tn->GetMass1()) * m_gQ_up2 * t_flow / (t_flow + m_tn->GetMass2());
				m_tn->m_pgQ_up += friction2 * GasFraction(m_tn->GetMass1(), t_flow + m_tn->GetMass2()) * (M2 / M) * m_gQ_up2 * t_flow / (t_flow + m_tn->GetMass1());*/

				m_gas2 = 0;

				/*m_gQ_up2 = 0;
				m_gQ_right2 = 0;
				m_gQ_down2 = 0;
				m_gQ_left2 = 0;*/
			}
			else
			{
				t_flow = m_gQ_up2 * deltatime;
				m_tn->m_pgas2 += t_flow;
				//t_flow *= M2;
				m_tn->m_pgQ_up += m_gQ_up2 * t_flow * M2;
				/*m_tn->m_pgQ_up2 += friction2 * GasFraction(t_flow + m_tn->GetMass2(), m_tn->GetMass1()) * m_gQ_up2 * t_flow / (t_flow + m_tn->GetMass2());
				m_tn->m_pgQ_up += friction2 * GasFraction(m_tn->GetMass1(), t_flow + m_tn->GetMass2()) * (M2 / M) * m_gQ_up2 * t_flow / (t_flow + m_tn->GetMass1());*/
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

double Cell::GetTotMass()
{
	return M * m_gas + M2 * m_gas2;
}

double Cell::GetMass1()
{
	return M * m_gas;
}

double Cell::GetMass2()
{
	return M2 * m_gas2;
}