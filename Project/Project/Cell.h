#pragma once

#include "SDL_rect.h"
#include "Vector2.h"

class Cell : public SDL_Rect
{
	double R = 8.3145;
	double T = 290.15;
	double M = 29;
public:
	double m_gas = 0; //mass
	double m_pgas;


	double m_gQ_up = 0;
	double m_gQ_right = 0;
	double m_gQ_down = 0;
	double m_gQ_left = 0;

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

	void AirPressureForce(double dt);

	void VelocityUpdate(double dt);

	void LateUpdate2(double dt);
	void LateUpdate3(double dt);
	
	void Receive(double p_water, Vector2 p_momentum);

	void SendWaterY(Cell *p_cell, int up, int down, double deltatime);
	void SendWaterX(Cell* p_cell, int left, int right, double deltatime);

	void AddForce(double p_upforce, double p_rightforce, double p_downforce, double p_leftforce);
};

