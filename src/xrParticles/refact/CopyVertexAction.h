#pragma once
#include "ParticleActionBase.h"

class CopyVertexAction final : public ParticleActionBase
{
public:
	CopyVertexAction(const bool& isCopyPosition);
	~CopyVertexAction() = default;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool IsCopyPosition() const;

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
	bool m_isCopyPosition;
};