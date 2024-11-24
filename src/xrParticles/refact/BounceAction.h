#pragma once
#include "ParticleShapeBase.h"
#include "ParticleActionBase.h"

class BounceAction final : public ParticleActionBase
{
public:
	BounceAction(ParticleShapeBase* positionShape, const float& oneMinusFriction, const float& resilence, const float& cutoffSquare);
	~BounceAction() = default;

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
	float OneMinusFriction() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float Resilence() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float CutoffSquare() const;

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
	ParticleShapeBase* m_localPosition;
	ParticleShapeBase* m_position;

	float m_omFriction;
	float m_cutoffSquare;
	float m_resilence;
};