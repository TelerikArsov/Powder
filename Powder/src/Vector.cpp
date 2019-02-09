#include "Vector.h"
#include <math.h>



double Vector::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector& Vector::Rotate2D(double angle)
{
	double xr = x * cos(angle) - y * sin(angle);
	double yr = y * sin(angle) + y * cos(angle);
	x = xr;
	y = yr;
	return *this;
}

Vector Vector::PerpendicularCW()
{
	return Vector(y, -x);
}

Vector Vector::Cross(const Vector& u, const Vector& v)
{
	return Vector(u.y * v.z - u.z * v.y,
				-u.x * v.z + u.z * v.x,
				u.x * v.y - u.y * v.x);
}

Vector Vector::Normalize(const Vector& u)
{
	return Vector(u.x, u.y, u.z).Normalize();
}

double Vector::TripleScalarProduct(const Vector & u, const Vector & v, const Vector & w) const
{
	return double((u.x * (v.y * w.z - v.z * w.y)) + 
				(u.y * (-v.x *w.z + v.z * w.x)) + 
				(u.z * (v.x * w.y - v.y * w.x)));
}

Vector& Vector::Normalize()
{
	double m = Magnitude();
	if (m <= tol)
		m = 1;     
	x /= m;     
	y /= m;     
	z /= m;
	if (fabs(x) < tol) 
		x = 0.0f;     
	if (fabs(y) < tol) 
		y = 0.0f;     
	if (fabs(z) < tol) 
		z = 0.0f;
	return *this;
}

Vector& Vector::Reverse()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

Vector& Vector::Zero()
{
	x = 0;
	y = 0;
	z = 0;
	return *this;
}

Vector& Vector::operator+=(const Vector& u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

Vector& Vector::operator=(const Vector& u)
{
	if (this != &u)
	{
		x = u.x;
		y = u.y;
		z = u.z;
	}
	return *this;
}

Vector& Vector::operator*=(const double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector& Vector::operator/=(const double s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

Vector operator+(Vector u, const Vector& v)
{
	return u += v;
}

Vector operator-(Vector u, const Vector& v)
{
	return u -= v;
}

double operator*(const Vector& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector operator*(Vector u, const double s)
{
	return u *= s;
}

Vector operator*(const double s, Vector u)
{
	return u *= s;
}

Vector operator/(Vector u, const double s)
{
	return u /= s;
}

Vector operator/(const double s, Vector u)
{
	return u /= s;
}
