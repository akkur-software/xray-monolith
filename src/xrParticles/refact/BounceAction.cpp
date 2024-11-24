#include "BounceAction.h"

BounceAction::BounceAction(ParticleShapeBase* positionShape, const float& oneMinusFriction, const float& resilence, const float& cutoffSquare) :
    m_localPosition(positionShape),
    m_position(positionShape),
    m_omFriction(oneMinusFriction),
    m_resilence(resilence),
    m_cutoffSquare(cutoffSquare)
{
}

ParticleShapeBase* BounceAction::LocalPositionShape() const
{
	return m_localPosition;
}

ParticleShapeBase* BounceAction::PositionShape() const
{
	return m_position;
}

float BounceAction::OneMinusFriction() const
{
	return m_omFriction;
}

float BounceAction::Resilence() const
{
	return m_resilence;
}

float BounceAction::CutoffSquare() const
{
	return m_cutoffSquare;
}

void BounceAction::Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
    switch (m_position->Type())
    {
    case ParticleShapeType::Plane:
        ProcessPlanePosition(effect, delta, maxLifeTime);
        break;
    case ParticleShapeType::Triangle:
        ProcessTrianglePosition(effect, delta, maxLifeTime);
        break;
    case ParticleShapeType::Sphere:
        ProcessSpherePosition(effect, delta, maxLifeTime);
        break;
    case ParticleShapeType::Disc:
        ProcessDiscPosition(effect, delta, maxLifeTime);
        break;
    case ParticleShapeType::Rectangle:
        ProcessRectanglePosition(effect, delta, maxLifeTime);
        break;
    default: break;
    }
}

void BounceAction::Transform(const Fmatrix& matrix)
{
    m_position->Transform(m_localPosition, matrix);
}

void BounceAction::Load(IReader& reader)
{
    m_flags.assign(reader.r_u32());
    m_type = (ParticleActionType)reader.r_u32();

    reader.r(&m_position, ParticleShapeBase::SizeOf());
    m_omFriction = reader.r_float();
    m_resilence = reader.r_float();
    m_cutoffSquare = reader.r_float();
    m_localPosition = m_position;
}

void BounceAction::Save(IWriter& writer)
{
    writer.w_u32(m_flags.get());
    writer.w_u32((uint32_t)m_type);

    writer.w(&m_position, ParticleShapeBase::SizeOf());
    writer.w_float(m_omFriction);
    writer.w_float(m_resilence);
    writer.w_float(m_cutoffSquare);
}

void BounceAction::ProcessPlanePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// Is there a faster way to do this?
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

		// Compute tangential and normal components of velocity
		float nmag = particle.Velocity * m_position->Point2();

		Pvector vn(m_position->Point2() * nmag); // Normal Vn = (V.N)N
		Pvector vt(particle.Velocity - vn); // Tangent Vt = V - Vn

		// Compute new velocity heading out:
		// Don't apply friction if tangential velocity < cutoff
		particle.Velocity = vt.Length2() <= m_cutoffSquare
			? vt - vn * m_resilence
			: vt * m_omFriction - vn * m_resilence;
	}
}

void BounceAction::ProcessRectanglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	// Compute the inverse matrix of the plane basis.
	auto& u = m_position->U();
	auto& v = m_position->V();

	// w = u cross v
	float wx = u.y * v.z - u.z * v.y;
	float wy = u.z * v.x - u.x * v.z;
	float wz = u.x * v.y - u.y * v.x;

	float detail = 1 / (wz * u.x * v.y - wz * u.y * v.x - u.z * wx * v.y - u.x * v.z * wy + v.z * wx * u.y + u.z *	v.x * wy);

	Pvector s1((v.y * wz - v.z * wy), (v.z * wx - v.x * wz), (v.x * wy - v.y * wx));
	s1 *= detail;
	Pvector s2((u.y * wz - u.z * wy), (u.z * wx - u.x * wz), (u.x * wy - u.y * wx));
	s2 *= -detail;

	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// Is there a faster way to do this?
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

		// Find position at the crossing point by parameterizing
		// p(t) = pos + vel * t
		// Solve dist(p(t),plane) = 0 e.g.
		// n * p(t) + D = 0 ->
		// n * p + t (n * v) + D = 0 ->
		// t = -(n * p + D) / (n * v)
		float t = -distanceOld / (m_position->Point2() * particle.Velocity);

		// Actual intersection point p(t) = pos + vel t
		Pvector particleHit(particle.Position + particle.Velocity * t);

		// Offset from origin in plane, p - origin
		Pvector offset(particleHit - m_position->Point1());

		// Dot product with basis vectors of old frame
		// in terms of new frame gives position in uv frame.
		float upos = offset * s1;
		float vpos = offset * s2;

		// Crossed plane outside bounce region if !(0<=[uv]pos<=1)
		if (upos < 0 || upos > 1 || vpos < 0 || vpos > 1)
		{
			continue;
		}

		// Compute tangential and normal components of velocity
		float nmag = particle.Velocity * m_position->Point2();

		Pvector vn(m_position->Point2() * nmag); // Normal Vn = (V.N)N
		Pvector vt(particle.Velocity - vn); // Tangent Vt = V - Vn

		// Compute new velocity heading out:
		// Don't apply friction if tangential velocity < cutoff
		particle.Velocity = vt.Length2() <= m_cutoffSquare
			? vt - vn * m_resilence
			: vt * m_omFriction - vn * m_resilence;
	}
}

void BounceAction::ProcessTrianglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	// Compute the inverse matrix of the plane basis.
	auto& u = m_position->U();
	auto& v = m_position->V();

	// w = u cross v
	float wx = u.y * v.z - u.z * v.y;
	float wy = u.z * v.x - u.x * v.z;
	float wz = u.x * v.y - u.y * v.x;

	float detail = 1 / (wz * u.x * v.y - wz * u.y * v.x - u.z * wx * v.y - u.x * v.z * wy + v.z * wx * u.y + u.z * v.x * wy);

	Pvector s1((v.y * wz - v.z * wy), (v.z * wx - v.x * wz), (v.x * wy - v.y * wx));
	s1 *= detail;

	Pvector s2((u.y * wz - u.z * wy), (u.z * wx - u.x * wz), (u.x * wy - u.y * wx));
	s2 *= -detail;

	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// Is there a faster way to do this?
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

		// Find position at the crossing point by parameterizing
		// p(t) = pos + vel * t
		// Solve dist(p(t),plane) = 0 e.g.
		// n * p(t) + D = 0 ->
		// n * p + t (n * v) + D = 0 ->
		// t = -(n * p + D) / (n * v)
		// Could factor n*v into distnew = distold + n*v and save a bit.
		// Safe since n*v != 0 assured by quick rejection test.
		// This calc is indep. of dt because we have established that it
		// will hit before dt. We just want to know when.
		float nv = m_position->Point2() * particle.Velocity;
		float t = -distanceOld / nv;

		// Actual intersection point p(t) = pos + vel t
		Pvector particleHit(particle.Position + particle.Velocity * t);

		// Offset from origin in plane, p - origin
		Pvector offset(particleHit - m_position->Point1());

		// Dot product with basis vectors of old frame
		// in terms of new frame gives position in uv frame.
		float upos = offset * s1;
		float vpos = offset * s2;

		// Did it cross plane outside triangle?
		if (upos < 0 || vpos < 0 || (upos + vpos) > 1)
		{
			continue;
		}

		// Compute tangential and normal components of velocity
		Pvector vn(m_position->Point2() * nv); // Normal Vn = (V.N)N
		Pvector vt(particle.Velocity - vn); // Tangent Vt = V - Vn

		// Compute new velocity heading out:
		// Don't apply friction if tangential velocity < cutoff
		particle.Velocity = vt.Length2() <= m_cutoffSquare
			? vt - vn * m_resilence
			: vt * m_omFriction - vn * m_resilence;
	}
}

void BounceAction::ProcessSpherePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	// Sphere that particles bounce off
	// The particles are always forced out of the sphere.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's next position is inside domain.
		// If so, bounce it.
		Pvector pnext(particle.Position + particle.Velocity * delta);

		if (m_position->IsWithin(pnext))
		{
			// See if we were inside on previous timestep.
			bool isInside = m_position->IsWithin(particle.Position);

			// Normal to surface. This works for a sphere. Isn't
			// computed quite right, should extrapolate particle
			// position to surface.
			Pvector n(particle.Position - m_position->Point1());
			n.normalize_safe();

			// Compute tangential and normal components of velocity
			float nmag = particle.Velocity * n;

			Pvector vn(n * nmag); // Normal Vn = (V.N)N
			Pvector vt = particle.Velocity - vn; // Tangent Vt = V - Vn

			if (isInside)
			{
				// Previous position was inside. If normal component of
				// velocity points in, reverse it. This effectively
				// repels particles which would otherwise be trapped
				// in the sphere.
				if (nmag < 0)
				{
					particle.Velocity = vt - vn;
				}
			}
			else
			{
				// Previous position was outside -> particle will cross
				// surface boundary. Reverse normal component of velocity,
				// and apply friction (if Vt >= cutoff) and resilience.

				// Compute new velocity heading out:
				// Don't apply friction if tangential velocity < cutoff
				particle.Velocity = vt.Length2() <= m_cutoffSquare
					? vt - vn * m_resilence
					: vt * m_omFriction - vn * m_resilence;
			}
		}
	}
}

void BounceAction::ProcessDiscPosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	auto outerRadiusSquare = _sqr(m_position->OuterRadius());
	auto innerRadiusSquare = _sqr(m_position->InnerRadius());

	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// Is there a faster way to do this?
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

		// Find position at the crossing point by parameterizing
		// p(t) = pos + vel * t
		// Solve dist(p(t),plane) = 0 e.g.
		// n * p(t) + D = 0 ->
		// n * p + t (n * v) + D = 0 ->
		// t = -(n * p + D) / (n * v)
		// Could factor n*v into distnew = distold + n*v and save a bit.
		// Safe since n*v != 0 assured by quick rejection test.
		// This calc is indep. of dt because we have established that it
		// will hit before dt. We just want to know when.
		float nv = m_position->Point2() * particle.Velocity;
		float t = -distanceOld / nv;

		// Actual intersection point p(t) = pos + vel t
		Pvector particleHit(particle.Position + particle.Velocity * t);

		// Offset from origin in plane, p - origin
		Pvector offset(particleHit - m_position->Point1());

		float radius = offset.Length2();

		if (radius > outerRadiusSquare || radius < innerRadiusSquare)
		{
			continue;
		}

		// Compute tangential and normal components of velocity
		Pvector vn(m_position->Point2() * nv); // Normal Vn = (V.N)N
		Pvector vt(particle.Velocity - vn); // Tangent Vt = V - Vn

		// Compute new velocity heading out:
		// Don't apply friction if tangential velocity < cutoff
		particle.Velocity = vt.Length2() <= m_cutoffSquare
			? vt - vn * m_resilence
			: vt * m_omFriction - vn * m_resilence;
	}
}
