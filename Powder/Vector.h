#pragma once
class Vector
{
public:
	double const tol = 0.0001f;
	double x;     
	double y;     
	double z;   
	double Magnitude() const;
	Vector& Rotate2D(double angle);
	Vector PerpendicularCW();
	static Vector Cross(const Vector& u, const Vector& v);
	static Vector Normalize(const Vector& u);
	double TripleScalarProduct(const Vector& u, const Vector& v, const Vector& w) const;
	Vector& Normalize();     
	Vector& Reverse();
	Vector& Zero();
	Vector& operator+=(const Vector& u);     
	Vector& operator-=(const Vector& u);  
	Vector& operator=(const Vector& u);
	Vector& operator*=(const double s);
	Vector& operator/=(const double s);
	Vector operator-() const;
	friend Vector operator+(Vector u, const Vector& v);
	friend Vector operator-(Vector u, const Vector& v);
	friend double operator*(const Vector& u, const Vector& v);
	friend Vector operator*(Vector u, const double s);
	friend Vector operator*(const double s, Vector u);
	friend Vector operator/(Vector u, const double s);
	friend Vector operator/(const double s, Vector u);
	Vector() : x(0), y(0), z(0)
	{
	}
	Vector(double x, double y, double z) : x(x), y(y), z(z)
	{
	}
	Vector(double x, double y) : x(x), y(y), z(0)
	{
	}
	~Vector()
	{
	}
};

