#pragma once
class Vector2
{

public:

	Vector2();
	~Vector2();

	double m_x=0, m_y=0;

	double Magnitude();
	double DistanceToPoint(Vector2& p_point);
	Vector2 Direction();
	Vector2 DirectionToPoint(Vector2& p_point);
	Vector2 Cross(Vector2& p_vector);

	Vector2 operator+(const Vector2& b);
	Vector2 operator-(const Vector2& b);
	double operator*(const Vector2& b);
	Vector2 operator*(const double& b);
	Vector2 operator/(const double& b);

};

