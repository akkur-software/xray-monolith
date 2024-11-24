#pragma once
#include "IParticleShapeFactory.h"

/// <summary>
/// 
/// </summary>
class DefaultParticleShapeFactory final : public IParticleShapeFactory
{
public:
	DefaultParticleShapeFactory() = default;
	~DefaultParticleShapeFactory() = default;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="shapeType"></param>
	/// <returns></returns>
	ParticleShapeBase* CreateShape(const ParticleShapeType& shapeType, const std::array<float, 9>& points);
};