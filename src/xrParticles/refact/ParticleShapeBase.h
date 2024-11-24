#pragma once
#include "ParticleVector.h"
#include "ParticleShapeType.h"

/// <summary>
/// The particle shape
/// </summary>
class ParticleShapeBase
{
public:
	virtual ~ParticleShapeBase() = default;

	ParticleShapeBase(const ParticleShapeBase&) = delete;
	ParticleShapeBase& operator=(const ParticleShapeBase&) = delete;
	
public:
	/// <summary>
	/// Type of the shape
	/// </summary>
	ParticleShapeType Type() const;

	/// <summary>
	/// First shape point
	/// </summary>
	Pvector Point1() const;

	/// <summary>
	/// Second shape point
	/// </summary>
	Pvector Point2() const;

	/// <summary>
	/// Orthonormal basis vector for Cylinder/Cone
	/// </summary>
	Pvector U() const;

	/// <summary>
	/// Orthonormal basis vector for Cylinder/Cone
	/// </summary>
	Pvector V() const;

	/// <summary>
	/// Outer radius of the shape
	/// </summary>
	float OuterRadius() const;

	/// <summary>
	/// Inner radius of the shape
	/// </summary>
	float InnerRadius() const;

	/// <summary>
	/// Used for fast Within test of spheres, and for mag. of u and v vectors for plane.
	/// </summary>
	float OuterRadiusSquare() const;

	/// <summary>
	/// Used for fast Within test of spheres, and for mag. of u and v vectors for plane.
	/// </summary>
	float InnerRadiusSquare() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static constexpr size_t SizeOf();

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	virtual bool IsWithin(const Pvector& vec) const = 0;

	/// <summary>
	/// Generate a random point uniformly distrbuted within the domain
	/// </summary>
	/// <returns></returns>
	virtual Pvector GeneratePoint() const = 0;

	/// <summary>
	/// Transformation
	/// </summary>
	/// <param name="matrix"></param>
	virtual void Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix) = 0;

	/// <summary>
	/// Direct transformation?
	/// </summary>
	/// <param name="matrix"></param>
	virtual void TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix) = 0;

protected:
	/// <summary>
	/// 
	/// </summary>
	ParticleShapeBase();

protected:
	ParticleShapeType m_type;

	Pvector m_point1;
	Pvector m_point2;
	Pvector m_u;
	Pvector m_v;

	float m_outerRadius;
	float m_innerRadius;
	float m_outerRadiusSquare;
	float m_innerRadiusSquare;
};