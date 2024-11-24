#pragma once

/// <summary>
	/// Types of particle actions
	/// </summary>
enum class ParticleActionType
{
	/// <summary>
	/// 
	/// </summary>
	Unknown = -1,

	/// <summary>
	/// Avoid entering the domain of space
	/// </summary>
	Avoid,

	/// <summary>
	/// Bounce particles off a domain of space
	/// </summary>
	Bounce,

	/// <summary>
	/// 
	/// </summary>
	CallActionListObsolette,

	/// <summary>
	/// Set the secondary position from current position
	/// </summary>
	CopyVertex,

	/// <summary>
	/// Dampen particle velocities.
	/// </summary>
	Damping,

	/// <summary>
	/// An explosion
	/// </summary>
	Explosion,

	/// <summary>
	/// Accelerate toward the previous particle in the effect
	/// </summary>
	Follow,

	/// <summary>
	/// Accelerate each particle toward each other particle
	/// </summary>
	Gravitate,

	/// <summary>
	/// Acceleration in the given direction
	/// </summary>
	Gravity,

	/// <summary>
	/// 
	/// </summary>
	Jet,

	/// <summary>
	/// 
	/// </summary>
	KillOld,

	/// <summary>
	/// 
	/// </summary>
	MatchVelocity,

	/// <summary>
	/// 
	/// </summary>
	Move,

	/// <summary>
	/// 
	/// </summary>
	OrbitLine,

	/// <summary>
	/// 
	/// </summary>
	OrbitPoint,

	/// <summary>
	/// 
	/// </summary>
	RandomAccel,

	/// <summary>
	/// 
	/// </summary>
	RandomDisplace,

	/// <summary>
	/// 
	/// </summary>
	RandomVelocity,

	/// <summary>
	/// 
	/// </summary>
	Restore,

	/// <summary>
	/// 
	/// </summary>
	Sink,

	/// <summary>
	/// 
	/// </summary>
	SinkVelocity,

	/// <summary>
	/// 
	/// </summary>
	Source,

	/// <summary>
	/// 
	/// </summary>
	SpeedLimit,

	/// <summary>
	/// 
	/// </summary>
	TargetColor,

	/// <summary>
	/// 
	/// </summary>
	TargetSize,

	/// <summary>
	/// 
	/// </summary>
	TargetRotate,

	/// <summary>
	/// 
	/// </summary>
	TargetRotateD,

	/// <summary>
	/// 
	/// </summary>
	TargetVelocity,

	/// <summary>
	/// 
	/// </summary>
	TargetVelocityD,

	/// <summary>
	/// 
	/// </summary>
	Vortex,

	/// <summary>
	/// 
	/// </summary>
	Turbulence,

	/// <summary>
	/// 
	/// </summary>
	Scatter
};