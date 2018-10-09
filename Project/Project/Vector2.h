#pragma once
class Vector2
{

public:

	Vector2();
	~Vector2();

	float m_x, m_y;

	float Magnitude();
	float DistanceToPoint(Vector2& p_point);
	Vector2 Direction();
	Vector2 DirectionToPoint(Vector2& p_point);
	Vector2 Cross(Vector2& p_vector);

	Vector2 operator+(const Vector2& b);
	Vector2 operator-(const Vector2& b);
	float operator*(const Vector2& b);
	Vector2 operator*(const float& b);
	Vector2 operator/(const float& b);

};

