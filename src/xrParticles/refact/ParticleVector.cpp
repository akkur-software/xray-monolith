#include "../stdafx.h"
#include "ParticleVector.h"

Pvector::Pvector(float x, float y, float z)
{
	set(x, y, z);
}

float Pvector::Length() const
{
	return _sqrt(x * x + y * y + z * z);
}

float Pvector::Length2() const
{
	return (x * x + y * y + z * z);
}

float Pvector::operator*(const Pvector& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

Pvector Pvector::operator*(const float& value) const
{
	return Pvector(x * value, y * value, z * value);
}

Pvector Pvector::operator/(const float& value) const
{
	float delim = value != 0.f 
		? value 
		: 1.f;

	float invs = 1.0f / delim;
	return Pvector(x * invs, y * invs, z * invs);
}

Pvector Pvector::operator+(const Pvector& vec) const
{
	return Pvector(x + vec.x, y + vec.y, z + vec.z);
}

Pvector Pvector::operator-(const Pvector& vec) const
{
	return Pvector(x - vec.x, y - vec.y, z - vec.z);
}

Pvector Pvector::operator^(const Pvector& vec) const
{
	return Pvector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

Pvector Pvector::operator-()
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

Pvector& Pvector::operator+=(const Pvector& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Pvector& Pvector::operator-=(const Pvector& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Pvector& Pvector::operator*=(const float& value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Pvector& Pvector::operator/=(const float& value)
{
	float delim = value != 0.f 
		? value 
		: 1.f;

	float invs = 1.0f / delim;

	x *= invs;
	y *= invs;
	z *= invs;

	return *this;
}

Pvector& Pvector::operator=(const Pvector& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return *this;
}
