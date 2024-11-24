#pragma once
#include "ParticleActionType.h"
#include "ParticleEffect.h"

/// <summary>
/// 
/// </summary>
class ParticleActionBase
{
public:
	virtual ~ParticleActionBase() = default;
	ParticleActionBase(const ParticleActionBase&) = delete;
	ParticleActionBase& operator=(const ParticleActionBase&) = delete;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ParticleActionType Type() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Flags32 Flags();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="effect"></param>
	/// <param name="delta"></param>
	/// <param name="maxLifeTime"></param>
	virtual void Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="matrix"></param>
	virtual void Transform( const Fmatrix& matrix) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="reader"></param>
	virtual void Load(IReader& reader) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="writer"></param>
	virtual void Save(IWriter& writer) = 0;

protected:
	ParticleActionBase();

protected:
	Flags32 m_flags;
	ParticleActionType m_type;
};