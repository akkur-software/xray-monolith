#pragma once
#include "IParticleShapeController.h"

/// <summary>
/// 
/// </summary>
__interface IParticleShapeControllerFactory
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="shapeType"></param>
	/// <returns></returns>
	IParticleShapeController* CreateController(const ParticleShapeType& shapeType);
};