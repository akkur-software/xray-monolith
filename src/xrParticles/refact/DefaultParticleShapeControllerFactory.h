#pragma once
#include "IParticleShapeControllerFactory.h"

/// <summary>
/// 
/// </summary>
class DefaultParticleShapeControllerFactory final : public IParticleShapeControllerFactory
{
public:
	DefaultParticleShapeControllerFactory() = default;
	~DefaultParticleShapeControllerFactory() = default;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="shapeType"></param>
	/// <returns></returns>
	IParticleShapeController* CreateController(const ParticleShapeType& shapeType);
};