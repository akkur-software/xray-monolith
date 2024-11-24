#pragma once
#include "ParticleShapeBase.h"
#include "ParticleActionBase.h"

class AvoidAction final : public ParticleActionBase
{
public:
	AvoidAction(ParticleShapeBase* positionShape, const float& lookAhead, const float& magnitude, const float& epsilon);
	~AvoidAction() = default;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ParticleShapeBase* LocalPositionShape() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ParticleShapeBase* PositionShape() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float LookAhead() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float Magnitude() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float Epsilon() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="effect"></param>
	/// <param name="delta"></param>
	/// <param name="maxLifeTime"></param>
	virtual void Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="matrix"></param>
	virtual void Transform(const Fmatrix& matrix) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="reader"></param>
	virtual void Load(IReader& reader) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="writer"></param>
	virtual void Save(IWriter& writer) override;

private:
	void ProcessPlanePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime);
	void ProcessRectanglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime);
	void ProcessTrianglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime);
	void ProcessSpherePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime);
	void ProcessDiscPosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime);

private:
	ParticleShapeBase* m_localPosition; // Avoid region (in local space)
	ParticleShapeBase* m_position; // Avoid region

	float m_lookAhead; // how many time units ahead to look
	float m_magnitude; // what percent of the way to go each time
	float m_epsilon; // add to r^2 for softening
};