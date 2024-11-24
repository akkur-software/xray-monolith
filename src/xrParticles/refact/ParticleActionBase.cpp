#include "stdafx.h"
#include "ParticleActionBase.h"

ParticleActionBase::ParticleActionBase() :
	m_flags(Flags32{}),
	m_type(ParticleActionType::Unknown)
{
}

ParticleActionType ParticleActionBase::Type() const
{
	return m_type;
}

Flags32 ParticleActionBase::Flags()
{
	return m_flags;
}
