#pragma once
#include "IParticleShapeController.h"

/// <summary>
/// 
/// </summary>
class ConeShapeController final : public IParticleShapeController
{
public:
	ConeShapeController() = default;
	~ConeShapeController() = default;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="vec"></param>
	/// <returns></returns>
	bool IsWithin(const ParticleShape& shape, const Pvector& vec) const;

	/// <summary>
	/// Transformation
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	ParticleShape Transform(const ParticleShape& shape, const Fmatrix& matrix);

	/// <summary>
	/// Direct transformation?
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	ParticleShape TransformDir(const ParticleShape& shape, const Fmatrix& matrix);

	/// <summary>
	/// Generate a random point uniformly distrbuted within the domain
	/// </summary>
	/// <param name="shape"></param>
	/// <returns></returns>
	Pvector GeneratePoint(const ParticleShape& shape) const;

	/// <summary>
	/// Construct a shape in the standard way
	/// </summary>
	/// <param name="p0"></param>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="p3"></param>
	/// <param name="p4"></param>
	/// <param name="p5"></param>
	/// <param name="p6"></param>
	/// <param name="p7"></param>
	/// <param name="p8"></param>
	/// <returns></returns>
	ParticleShape Create(
		float p0 = 0.0f, float p1 = 0.0f, float p2 = 0.0f,
		float p3 = 0.0f, float p4 = 0.0f, float p5 = 0.0f,
		float p6 = 0.0f, float p7 = 0.0f, float p8 = 0.0f);
};