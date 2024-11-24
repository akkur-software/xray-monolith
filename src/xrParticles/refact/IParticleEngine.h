#pragma once
#include "../../xrCore/xrCore.h"
#include "ParticleActionBase.h"
#include "ParticleCallbacks.h"

/// <summary>
/// 
/// </summary>
__interface IParticleEngine
{	
	int CreateEffect(uint32_t maxParticleCount);
	void DestroyEffect(const int32_t& effectId);

	int CreateActionList();
	void DestroyActionList(const int32_t& actionListId);

	void PlayEffect(const int32_t& effectId, const int32_t& actionListId);
	void StopEffect(const int32_t& effectId, const int32_t& actionListId, const bool& isDeffered = true);

	void Update(const int32_t& effectId, const int32_t& actionListId, const float& delta);
	void Transform(const int32_t& actionListId, const Fmatrix& matrix, const Fvector& velocity);

	void RemoveParticle(const int32_t& effectId, const uint32_t& particleId);
	void SetMaxParticles(const int32_t& effectId, const uint32_t& maxParticleCount);
	void SetBirthCallback(const int32_t& effectId, const OnBirthParticle& callback, void* owner, const uint32_t& param);
	void SetDeathCallback(const int32_t& effectId, const OnDeadParticle& callback, void* owner, const uint32_t& param);
	void GetParticles(const int32_t& effectId, const uint32_t& count);
	size_t GetParticlesCount(const int32_t& effectId);

	ParticleActionBase* CreateEmptyAction(const ParticleActionType& type);
	uint32_t LoadActions(const int32_t& actionListId, IReader& reader);
	void SaveActions(const int32_t& actionListId, IWriter& writer);
};