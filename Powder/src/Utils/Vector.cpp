#include "Utils/Vector.h"
#include <math.h>



float Vector::Magnitude() const
{
	return sqrtf(x * x + y * y);
}


Vector& Vector::PerpendicularCW()
{
	float tmp = x;
	x = y;
	y = -tmp;
	return *this;
}

Vector Vector::Normalize(const Vector& u)
{
	return Vector(u.x, u.y).Normalize();
}

Vector Vector::PerpendicularCW(const Vector & u)
{
	return Vector(u.y, -u.x);
}

Vector Vector::ReverseY(const Vector & u)
{
	return Vector(u.x, -u.y);
}

Vector& Vector::Normalize()
{
	float m = Magnitude();
	if (m <= tol)
		m = 1;     
	x /= m;     
	y /= m;     
	if (fabs(x) < tol) 
		x = 0.0f;     
	if (fabs(y) < tol) 
		y = 0.0f;
	return *this;
}

Vector& Vector::Reverse()
{
	x = -x;
	y = -y;
	return *this;
}

Vector& Vector::ReverseY()
{
	y = -y;
	return *this;
}

Vector& Vector::Zero()
{
	x = 0;
	y = 0;
	return *this;
}

Vector& Vector::operator+=(const Vector& u)
{
	x += u.x;
	y += u.y;
	return *this;
}

Vector& Vector::operator-=(const Vector& u)
{
	x -= u.x;
	y -= u.y;
	return *this;
}

Vector& Vector::operator=(const Vector& u)
{
	if (this != &u)
	{
		x = u.x;
		y = u.y;
	}
	return *this;
}

Vector& Vector::operator*=(const float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector& Vector::operator/=(const float s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector Vector::operator-() const
{
	return Vector(-x, -y);
}

Vector operator+(Vector u, const Vector& v)
{
	return u += v;
}

Vector operator-(Vector u, const Vector& v)
{
	return u -= v;
}

float operator*(const Vector& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y;
}

Vector operator*(Vector u, const float s)
{
	return u *= s;
}

Vector operator*(const float s, Vector u)
{
	return u *= s;
}

Vector operator/(Vector u, const float s)
{
	return u /= s;
}

Vector operator/(const float s, Vector u)
{
	return u /= s;
}
