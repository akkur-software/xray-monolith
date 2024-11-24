#pragma once
#include <array>
#include "ParticleShapeBase.h"

/// <summary>
/// 
/// </summary>
class BlobShape final : public ParticleShapeBase
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="points"></param>
	BlobShape(const std::array<float, 9>& points);
	~BlobShape() = default;

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
	/// <param name="shape"></param>
	/// <returns></returns>
	Pvector GeneratePoint() const override;

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