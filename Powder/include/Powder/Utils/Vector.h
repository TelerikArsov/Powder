#pragma once
class Vector
{
public:
	float const tol = 0.0001f;
	float x;     
	float y;      
	float Magnitude() const;
	static Vector Normalize(const Vector& u);
	static Vector PerpendicularCW(const Vector& u);
	Vector& PerpendicularCW();
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
	Vector() : x(0), y(0)
	{
	}
	Vector(float x, float y) : x(x), y(y)
	{
	}

	Vector(int x, int y) :
		x(static_cast<float> (x)),
		y(static_cast<float> (y))
	{
	}

	~Vector()
	{
	}
};

