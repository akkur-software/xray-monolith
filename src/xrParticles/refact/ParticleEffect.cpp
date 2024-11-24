#include "stdafx.h"
#include <stdexcept>
#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(size_t maxParticleCount) : 
	m_particles(std::vector<Particle>{}),
	m_maxCount(maxParticleCount)
{
	m_particles.reserve(maxParticleCount);
}

ParticleEffect::~ParticleEffect()
{
	RemoveAll();
}

size_t ParticleEffect::Count() const
{
	return m_particles.size();
}

size_t ParticleEffect::MaxCount() const
{
	return m_maxCount;
}

size_t ParticleEffect::Size() const
{
	return m_particles.size() * sizeof(Particle);
}

const Particle* ParticleEffect::Pointer() const
{
	return m_particles.data();
}

Particle ParticleEffect::Get(uint32_t index) const
{
	if (!m_particles.empty() && index < m_particles.size())
	{
		return m_particles[index];
	}
	else
	{
		throw std::out_of_range("Invalid particle index");
	}
}

bool ParticleEffect::Add(const Particle& particle)
{
	auto currentSize = m_particles.size();
	
	if (currentSize < m_maxCount)
	{
		m_particles.emplace_back(particle);
		return m_particles.size() == currentSize + 1;
	}
	else
	{
		return false;
	}
}

void ParticleEffect::Remove(uint32_t index)
{
	if (!m_particles.empty() && index < m_particles.size())
	{
		if (index > 0)
		{
			std::swap(m_particles[index], m_particles.back());
		}
		m_particles.pop_back();
	}
}

void ParticleEffect::RemoveAll()
{
	m_particles.clear();
}
