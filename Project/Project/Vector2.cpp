#include "Vector2.h"
#include "math.h"
//#include <iostream>
//using namespace std;

Vector2::Vector2()
{

}

Vector2::~Vector2()
{

}

float Vector2::Magnitude()
{
	return sqrtf((m_x * m_x) + (m_y * m_y));
}

float Vector2::DistanceToPoint(Vector2& p_point)
{
	return (*this - p_point).Magnitude();
}

Vector2 Vector2::Direction()
{
	return *this / Magnitude();
}

Vector2 Vector2::DirectionToPoint(Vector2& p_point)
{
	return (*this - p_point) / DistanceToPoint(p_point);
}

Vector2 Vector2::Cross(Vector2& p_vector)
{
	Vector2 t_Vector;
	t_Vector.m_x = (m_x*p_vector.m_y) - (m_y*p_vector.m_x);
	t_Vector.m_y = (m_y*p_vector.m_x) - (m_x*p_vector.m_y);
	return t_Vector;
}

Vector2 Vector2::operator+(const Vector2& p_Addend)
{
	Vector2 t_Vector;
	t_Vector.m_x = m_x + p_Addend.m_x;
	t_Vector.m_y = m_y + p_Addend.m_y;
	return t_Vector;
}

Vector2 Vector2::operator-(const Vector2& p_Subtrahend)
{
	Vector2 t_Vector; 
	t_Vector.m_x = m_x - p_Subtrahend.m_x;
	t_Vector.m_y = m_y - p_Subtrahend.m_y;
	return t_Vector;
}

float Vector2::operator*(const Vector2& p_Vector)
{
	return (m_x * p_Vector.m_x) + (m_y + p_Vector.m_y);
}

Vector2 Vector2::operator*(const float& p_multiplier)
{
	Vector2 t_Vector;
	t_Vector.m_x *= p_multiplier;
	t_Vector.m_y *= p_multiplier;
	return t_Vector;
}

Vector2 Vector2::operator/(const float& p_divisor)
{
	Vector2 t_Vector;
	t_Vector.m_x /= p_divisor;
	t_Vector.m_y /= p_divisor;
	return t_Vector;
}