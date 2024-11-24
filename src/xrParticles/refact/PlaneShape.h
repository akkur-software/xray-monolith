#pragma once
#include <array>
#include "ParticleShapeBase.h"

/// <summary>
/// 
/// </summary>
class PlaneShape final : public ParticleShapeBase
{
public:
	PlaneShape(const std::array<float, 9>& points);
	~PlaneShape() = default;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	virtual bool IsWithin(const Pvector& vec) const override;

	/// <summary>
	/// Generate a random point uniformly distrbuted within the domain
	/// </summary>
	/// <returns></returns>
	virtual Pvector GeneratePoint() const override;

	/// <summary>
	/// Transformation
	/// </summary>
	/// <param name="matrix"></param>
	virtual void Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix) override;

	/// <summary>
	/// Direct transformation?
	/// </summary>
	/// <param name="matrix"></param>
	virtual void TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix) override;
};