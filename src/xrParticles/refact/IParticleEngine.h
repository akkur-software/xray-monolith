#pragma once
#include "../../xrCore/xrCore.h"
#include "ParticleActionType.h"
#include "ParticleCallbacks.h"

struct ParticleAction;

/// <summary>
/// 
/// </summary>
__interface IParticleEngine
{
	int CreateEffect(u32 maxParticleCount);
	void DestroyEffect(int effectId);

	int CreateActionList();
	void DestroyActionList(int actionListId);

	void PlayEffect(int effectId, int actionListId);
	void StopEffect(int effectId, int actionListId, bool isDeffered = true);

	void Update(int effectId, int actionListId, float dt);
	void Render(int effectId);
	void Transform(int actionListId, const Fmatrix& matrix, const Fvector& velocity);

	void RemoveParticle(int effectId, u32 particleId);
	void SetMaxParticles(int effectId, u32 maxParticleCount);
	void SetBirthCallback(int effectId, OnBirthParticle b, void* owner, u32 param);
	void SetDeathCallback(int effectId, OnDeadParticle b, void* owner, u32 param);
	void GetParticles(int effectId, Particle*& particles, u32& count);
	u32 GetParticlesCount(int effectId);

	ParticleAction* CreateAction(ParticleActionType type);
	u32 LoadActions(int actionListId, IReader& reader);
	void SaveActions(int actionListId, IWriter& writer);
};