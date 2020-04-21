#pragma once

#include "SDL_rect.h"
#include "Vector2.h"

class Cell : public SDL_Rect
{

public:
	double m_water = 0;
	double m_viscosity = 0;
	Vector2 m_velocity;
//	float m_salt;
//	float m_temperature;
//	float m_playermass;
//	float m_pressure;
//	Vector2 m_force;

	bool m_pressurized = false;
	double m_pressure_top = 0;
	double m_pressure_bot = 0;
	double m_pressure_right = 0;
	double m_pressure_left = 0;
	double m_total_pressure = 0;

	double m_pending_force_top = 0;
	double m_pending_force_bot = 0;
	double m_pending_force_right = 0;
	double m_pending_force_left = 0;

//	Uint32 m_r;
//	Uint32 m_g;
	Uint32 m_b = 0;
//	Uint32 m_a;

	double m_excess_water = 0;
	double m_pressure = 0;
//	float m_pending_salt;
//	float m_pending_temperature;
//	Vector2 m_pending_force;

	double m_volume = 0;

	Cell *m_top_neighbour_cell = nullptr;
	Cell *m_right_neighbour_cell = nullptr;
	Cell *m_bot_neighbour_cell = nullptr;
	Cell *m_left_neighbour_cell = nullptr;

	int m_top_not_full = 0;
	int m_right_not_full = 0;
	int m_bot_not_full = 0;
	int m_left_not_full = 0;

	float MaxDensity(double p_pressure);

public:
	Cell();
	~Cell();

	void Initialize(Cell *p_top_neighbour, Cell *p_right_neighbour, Cell *p_bot_neighbour, Cell *p_left_neighbour);
	void EarlyUpdate(double deltatime);
	void Update(double deltatime);
	void LateUpdate(double deltatime);
	void LateUpdate2(double deltatime);
	void LateUpdate3(double deltatime);
	double Receive(double p_water, Vector2 p_momentum);

	void SendWaterY(Cell *p_cell, int up, int down, double deltatime);
	void SendWaterX(Cell* p_cell, int left, int right, double deltatime);

	void AddForce(double p_upforce, double p_rightforce, double p_downforce, double p_leftforce);
};

