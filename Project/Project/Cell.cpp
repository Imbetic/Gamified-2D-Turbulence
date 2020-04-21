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
	m_gas = 0 + 0.1 * (double)((rand() % 5) + 1);
	
	m_gP = 0;
	m_excess_fluid = 0;

	m_tn = p_top_neighbour;
	m_rn = p_right_neighbour;
	m_bn = p_bot_neighbour;
	m_ln = p_left_neighbour;
	
}

void Cell::Density1(double deltatime)
{

}

void Cell::SendWaterY(Cell *p_cell, int up, int down, double deltatime)
{

}

void Cell::SendWaterX(Cell* p_cell, int left, int right, double deltatime)
{

}

void Cell::Update(double deltatime)
{

}

void Cell::LateUpdate(double deltatime)
{

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