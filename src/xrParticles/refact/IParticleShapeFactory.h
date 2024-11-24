#pragma once
#include <array>
#include "ParticleShapeBase.h"

/// <summary>
/// 
/// </summary>
__interface IParticleShapeFactory
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="shapeType"></param>
	/// <returns></returns>
	ParticleShapeBase* CreateShape(const ParticleShapeType& shapeType, const std::array<float, 9>& points);
};