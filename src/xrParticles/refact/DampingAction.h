#pragma once
#include "ParticleActionBase.h"

class DampingAction final : public ParticleActionBase
{
public:
	DampingAction(const Pvector& damping, const float& lowSquare, const float& highSquare);
	~DampingAction() = default;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Pvector Damping() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float LowSquare() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float HighSquare() const;

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
	Pvector m_damping; // Damping constant applied to velocity
	float m_lowSquare; // Low and high cutoff velocities
	float m_highSquare;
};