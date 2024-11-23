#pragma once
#include "ParticleVector.h"
#include "ParticleShapeType.h"

/// <summary>
/// The particle shape
/// </summary>
struct ParticleShape final
{
	/// <summary>
	/// Type of the shape
	/// </summary>
	ParticleShapeType Type;

	/// <summary>
	/// First shape point
	/// </summary>
	Pvector Point1;

	/// <summary>
	/// Second shape point
	/// </summary>
	Pvector Point2;

	/// <summary>
	/// Orthonormal basis vector for Cylinder/Cone
	/// </summary>
	Pvector U;

	/// <summary>
	/// Orthonormal basis vector for Cylinder/Cone
	/// </summary>
	Pvector V;

	/// <summary>
	/// Outer radius of the shape
	/// </summary>
	float OuterRadius;

	/// <summary>
	/// Inner radius of the shape
	/// </summary>
	float InnerRadius;

	/// <summary>
	/// Used for fast Within test of spheres, and for mag. of u and v vectors for plane.
	/// </summary>
	float OuterRadiusSquare;

	/// <summary>
	/// Used for fast Within test of spheres, and for mag. of u and v vectors for plane.
	/// </summary>
	float InnerRadiusSquare;
};