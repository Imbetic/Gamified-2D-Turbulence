#pragma once

#include "SDL_rect.h"
#include "Vector2.h"

class Cell : public SDL_Rect
{
	double R =8.3145;
	double T = 290.15;
	double T2 = 290.15;
	
public:

	double m_gas = 0; //mass
	double m_pgas =0;
	double M = 50;

	double m_gQ_up = 0;
	double m_gQ_right = 0;
	double m_gQ_down = 0;
	double m_gQ_left = 0;

	double m_pgQ_up = 0;
	double m_pgQ_right = 0;
	double m_pgQ_down = 0;
	double m_pgQ_left = 0;

	//double m_gasaccy2 = 0;
	//double m_gasaccx2 = 0;

	double m_gas2 = 0; //mass
	double m_pgas2 =0;
	double M2 = 29;

	double m_gQ_up2 = 0;
	double m_gQ_right2 = 0;
	double m_gQ_down2 = 0;
	double m_gQ_left2 = 0;

	double m_pgQ_up2 = 0;
	double m_pgQ_right2 = 0;
	double m_pgQ_down2 = 0;
	double m_pgQ_left2 = 0;

	double m_excess_fluid = 0;
	double m_gP = 0;

	double m_max_volume = 1;

	Cell *m_tn = nullptr;
	Cell *m_rn = nullptr;
	Cell *m_bn = nullptr;
	Cell *m_ln = nullptr;

public:
	Cell();
	~Cell();

	void Initialize(Cell *p_tn, Cell *p_rn, Cell *p_bn, Cell *p_ln);
	
	void AirPressure();

	void AirPressureForce(double dt, double xacc, double yacc);

	void VelocityUpdate(double dt);

	void LateUpdate2(double dt);
	void LateUpdate3(double dt);
	
	void Receive(double p_water, Vector2 p_momentum);

	void SendWaterY(Cell *p_cell, int up, int down, double deltatime);
	void SendWaterX(Cell* p_cell, int left, int right, double deltatime);

	void AddForce(double p_upforce, double p_rightforce, double p_downforce, double p_leftforce);

	double GasFraction(double gas1, double gas2);
};

