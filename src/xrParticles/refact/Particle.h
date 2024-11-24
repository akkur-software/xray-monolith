#pragma once
#include "ParticleVector.h"

/// <summary>
/// 
/// </summary>
struct Particle
{
	/// <summary>
	/// 
	/// </summary>
	float Rotation;

	/// <summary>
	/// 
	/// </summary>
	Pvector Position;

	/// <summary>
	/// 
	/// </summary>
	Pvector PositionB;

	/// <summary>
	/// 
	/// </summary>
	Pvector Velocity;

	/// <summary>
	/// 
	/// </summary>
	Pvector Size;
	
	/// <summary>
	/// 
	/// </summary>
	float ColorRed;

	/// <summary>
	/// 
	/// </summary>
	float ColorGreen;

	/// <summary>
	/// 
	/// </summary>
	float ColorBlue;

	/// <summary>
	/// 
	/// </summary>
	float ColorAlpha;

	/// <summary>
	/// 
	/// </summary>
	float Age;

	/// <summary>
	/// 
	/// </summary>
	u16 Frame;

	/// <summary>
	/// 
	/// </summary>
	Flags16 Flags;
};
