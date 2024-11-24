#pragma once
#include "../../xrCore/xrCore.h"
#include "ParticleActionType.h"
#include "ParticleEffect.h"

/// <summary>
/// 
/// </summary>
__interface IParticleAction
{
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Flags32 Flags();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ParticleActionType Type() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="effect"></param>
	/// <param name="dt"></param>
	/// <param name="m_max"></param>
	void Execute(const ParticleEffect& effect, const float& dt, float& m_max);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="matrix"></param>
	void Transform( const Fmatrix& matrix);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="reader"></param>
	void Load(IReader& reader);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="writer"></param>
	void Save(IWriter& writer);
};