#include "stdafx.h"
#include "CopyVertexAction.h"

CopyVertexAction::CopyVertexAction(const bool& isCopyPosition) : 
	m_isCopyPosition(isCopyPosition)
{
}

bool CopyVertexAction::IsCopyPosition() const
{
	return m_isCopyPosition;
}

void CopyVertexAction::Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	if (m_isCopyPosition)
	{
		for (u32 i = 0; i < effect.Count(); ++i)
		{			
			Particle& particle = effect.Get(i);
			particle.PositionB = particle.Position;
		}
	}
}

void CopyVertexAction::Transform(const Fmatrix& matrix)
{
}

void CopyVertexAction::Load(IReader& reader)
{
	m_flags.assign(reader.r_u32());
	m_type = (ParticleActionType)reader.r_u32();
	m_isCopyPosition = (bool)reader.r_u8();
}

void CopyVertexAction::Save(IWriter& writer)
{
	writer.w_u32(m_flags.get());
	writer.w_u32((uint32_t)m_type);
	writer.w_u8((uint8_t)m_isCopyPosition);
}
