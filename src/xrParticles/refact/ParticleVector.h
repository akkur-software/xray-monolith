#pragma once
#include "../../xrCore/xrCore.h"

class Pvector final : public Fvector
{
public:
	Pvector() = default;
	~Pvector() = default;

	Pvector(float x, float y, float z);

	float Length() const;
	float Length2() const;

	float operator*(const Pvector& vec) const;
	Pvector operator*(const float& value) const;
	Pvector operator/(const float& value) const;
	Pvector operator+(const Pvector& vec) const;
	Pvector operator-(const Pvector& vec) const;
	Pvector operator^(const Pvector& vec) const;

	Pvector operator-();
	Pvector& operator+=(const Pvector& vec);
	Pvector& operator-=(const Pvector& vec);
	Pvector& operator*=(const float& value);
	Pvector& operator/=(const float& value);
	Pvector& operator=(const Pvector& vec);
};