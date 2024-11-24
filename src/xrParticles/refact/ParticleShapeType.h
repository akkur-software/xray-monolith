#pragma once

/// <summary>
/// Types of particle shapes
/// </summary>
enum class ParticleShapeType
{
	/// <summary>
	/// Unknown shape
	/// </summary>
	Unknown = -1,

	/// <summary>
	/// Single point
	/// </summary>
	Point = 0,

	/// <summary>
	/// Line segment
	/// </summary>
	Line,

	/// <summary>
	/// Triangle
	/// </summary>
	Triangle,

	/// <summary>
	/// Arbitrarily-oriented plane
	/// </summary>
	Plane,

	/// <summary>
	/// Axis-aligned box
	/// </summary>
	Box,

	/// <summary>
	/// Sphere
	/// </summary>
	Sphere,

	/// <summary>
	/// Cylinder
	/// </summary>
	Cylinder,

	/// <summary>
	/// Cone
	/// </summary>
	Cone,

	/// <summary>
	/// Gaussian blob
	/// </summary>
	Blob,

	/// <summary>
	/// Arbitrarily-oriented disc
	/// </summary>
	Disc,

	/// <summary>
	/// Rhombus-shaped planar region
	/// </summary>
	Rectangle
};