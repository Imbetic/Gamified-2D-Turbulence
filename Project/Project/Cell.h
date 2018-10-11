#pragma once

#include "SDL_rect.h"
#include "Vector2.h"

class Cell : public SDL_Rect
{

private:
	float m_water;
	float m_viscosity;
	Vector2 m_pressure_gradient;
//	float m_salt;
//	float m_temperature;
//	float m_playermass;
//	float m_pressure;
//	Vector2 m_force;

//	Uint32 m_r;
//	Uint32 m_g;
	Uint32 m_b;
//	Uint32 m_a;

	float m_pending_water;
//	float m_pending_salt;
//	float m_pending_temperature;
//	Vector2 m_pending_force;

	float m_volume;

	Cell *m_top_neighbour_cell;
	Cell *m_right_neighbour_cell;
	Cell *m_bot_neighbour_cell;
	Cell *m_left_neighbour_cell;

	float MaxDensity(float p_pressure);

public:
	Cell();
	~Cell();

	void Initialize(Cell *p_top_neighbour, Cell *p_right_neighbour, Cell *p_bot_neighbour, Cell *p_left_neighbour);
	void Receive(float p_water, float p_salt, float p_temperature);
	void Update();
};

