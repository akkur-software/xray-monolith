#include "stdafx.h"
#include "DampingAction.h"

DampingAction::DampingAction(const Pvector& damping, const float& lowSquare, const float& highSquare) :
	m_damping(damping),
	m_lowSquare(lowSquare),
	m_highSquare(highSquare)
{
}

Pvector DampingAction::Damping() const
{
	return m_damping;
}

float DampingAction::LowSquare() const
{
	return m_lowSquare;
}

float DampingAction::HighSquare() const
{
	return m_highSquare;
}

void DampingAction::Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	// This is important if dt is != 1.
	Pvector one(1, 1, 1);
	Pvector scale(one - ((one - m_damping) * delta));

	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);
		float velocitySquare = particle.Velocity.Length2();

		if (velocitySquare >= m_lowSquare && velocitySquare <= m_highSquare)
		{
			particle.Velocity.x *= scale.x;
			particle.Velocity.y *= scale.y;
			particle.Velocity.z *= scale.z;
		}
	}
}

void DampingAction::Transform(const Fmatrix& matrix)
{
}

void DampingAction::Load(IReader& reader)
{
	m_flags.assign(reader.r_u32());
	m_type = (ParticleActionType)reader.r_u32();
	reader.r_fvector3(m_damping);
	m_lowSquare = reader.r_float();
	m_highSquare = reader.r_float();
}

void DampingAction::Save(IWriter& writer)
{
	writer.w_u32(m_flags.get());
	writer.w_u32((uint32_t)m_type);
	writer.w_fvector3(m_damping);
	writer.w_float(m_lowSquare);
	writer.w_float(m_highSquare);
}
