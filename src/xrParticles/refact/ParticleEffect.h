#pragma once
#include <stdint.h>
#include <vector>
#include "Particle.h"
#include "ParticleCallbacks.h"

/// <summary>
/// 
/// </summary>
class ParticleEffect final
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="maxParticleCount"></param>
	ParticleEffect(size_t maxParticleCount);

	/// <summary>
	/// 
	/// </summary>
	~ParticleEffect();

public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t Count() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t MaxCount() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t Size() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const Particle* Pointer() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	Particle Get(uint32_t index) const;
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="particle"></param>
	/// <returns></returns>
	bool Add(const Particle& particle);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	void Remove(uint32_t index);

	/// <summary>
	/// 
	/// </summary>
	void RemoveAll();

private:
	std::vector<Particle> m_particles;
	size_t m_maxCount;
};