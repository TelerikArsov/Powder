#pragma once
class Vector
{
public:
	float const tol = 0.0001f;
	float x;     
	float y;     
	float z;   
	float Magnitude() const;
	Vector& Rotate2D(float angle);
	Vector PerpendicularCW();
	static Vector Cross(const Vector& u, const Vector& v);
	static Vector Normalize(const Vector& u);
	float TripleScalarProduct(const Vector& u, const Vector& v, const Vector& w) const;
	Vector& Normalize();     
	Vector& Reverse();
	Vector& ReverseY();
	Vector& Zero();
	Vector& operator+=(const Vector& u);     
	Vector& operator-=(const Vector& u);  
	Vector& operator=(const Vector& u);
	Vector& operator*=(const float s);
	Vector& operator/=(const float s);
	Vector operator-() const;
	friend Vector operator+(Vector u, const Vector& v);
	friend Vector operator-(Vector u, const Vector& v);
	friend float operator*(const Vector& u, const Vector& v);
	friend Vector operator*(Vector u, const float s);
	friend Vector operator*(const float s, Vector u);
	friend Vector operator/(Vector u, const float s);
	friend Vector operator/(const float s, Vector u);
	Vector() : x(0), y(0), z(0)
	{
	}
	Vector(float x, float y, float z) : x(x), y(y), z(z)
	{
	}
	Vector(float x, float y) : x(x), y(y), z(0)
	{
	}

	Vector(int x, int y, int z) :
		x(static_cast<float> (x)),
		y(static_cast<float> (y)),
		z(static_cast<float> (z))
	{
	}
	Vector(int x, int y) :
		x(static_cast<float> (x)),
		y(static_cast<float> (y)),
		z(0)
	{
	}

	~Vector()
	{
	}
};

