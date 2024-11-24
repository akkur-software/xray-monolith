#pragma once
#include <stdint.h>
#include "Particle.h"

/// <summary>
/// 
/// </summary>
typedef void (*OnBirthParticle)(void* owner, uint32_t param, Particle& particle, uint32_t index);

/// <summary>
/// 
/// </summary>
typedef void (*OnDeadParticle)(void* owner, uint32_t param, Particle& particle, uint32_t index);