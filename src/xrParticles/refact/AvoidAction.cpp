#include "stdafx.h"
#include "AvoidAction.h"

AvoidAction::AvoidAction(ParticleShapeBase* positionShape, const float& lookAhead, const float& magnitude, const float& epsilon) : 
    m_localPosition(positionShape),
    m_position(positionShape),
    m_lookAhead(lookAhead),
    m_magnitude(magnitude),
    m_epsilon(epsilon)
{
}

ParticleShapeBase* AvoidAction::LocalPositionShape() const
{
    return m_localPosition;
}

ParticleShapeBase* AvoidAction::PositionShape() const
{
    return m_position;
}

float AvoidAction::LookAhead() const
{
    return m_lookAhead;
}

float AvoidAction::Magnitude() const
{
    return m_magnitude;
}

float AvoidAction::Epsilon() const
{
    return m_epsilon;
}

void AvoidAction::Execute(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
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

void AvoidAction::Transform(const Fmatrix& matrix)
{
    m_position->Transform(m_localPosition, matrix);
}

void AvoidAction::Load(IReader& reader)
{
    m_flags.assign(reader.r_u32());
    m_type = (ParticleActionType)reader.r_u32();

    reader.r(&m_position, ParticleShapeBase::SizeOf());
    m_lookAhead = reader.r_float();
    m_magnitude = reader.r_float();
    m_epsilon = reader.r_float();
    m_localPosition = m_position;
}

void AvoidAction::Save(IWriter& writer)
{
    writer.w_u32(m_flags.get());
    writer.w_u32((uint32_t)m_type);

    writer.w(&m_position, ParticleShapeBase::SizeOf());
    writer.w_float(m_lookAhead);
    writer.w_float(m_magnitude);
    writer.w_float(m_epsilon);
}

void AvoidAction::ProcessPlanePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
    auto magDelta = m_magnitude * delta;  
    
    for (u32 i = 0; i < effect.Count(); ++i)
    {
        Particle& particle = effect.Get(i);

        // point2 stores the plane normal (the a,b,c of the plane eqn).
        // Old and new distances: dist(p,plane) = n * p + d
        // outer radius stores -n*p, which is d.
        auto distance = particle.Position * m_position->Point2() + m_position->OuterRadius();
        auto isVelocityChangeAllowed = !(m_lookAhead < MAX_FLOAT && distance >= m_lookAhead);

        if (isVelocityChangeAllowed)
        {
            auto velocityLength = particle.Velocity.Length();
            auto Vn = particle.Velocity / velocityLength;
            auto tmp = (m_position->Point2() * (magDelta / (distance * distance + m_epsilon))) + Vn;

            particle.Velocity = tmp * (velocityLength / tmp.Length());
        }
    }
}

void AvoidAction::ProcessRectanglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	auto magDelta = m_magnitude * delta;
	
	// Compute the inverse matrix of the plane basis.
	auto& u = m_position->U();
	auto& v = m_position->V();

	// The normalized bases are needed inside the loop.
	auto un = u / m_position->OuterRadiusSquare();
	auto vn = v / m_position->InnerRadiusSquare();

	// w = u cross v
	auto wx = u.y * v.z - u.z * v.y;
	auto wy = u.z * v.x - u.x * v.z;
	auto wz = u.x * v.y - u.y * v.x;

	auto detail = 1 / (wz * u.x * v.y - wz * u.y * v.x - u.z * wx * v.y - u.x * v.z * wy + v.z * wx * u.y + u.z * v.x * wy);

	Pvector s1((v.y * wz - v.z * wy), (v.z * wx - v.x * wz), (v.x * wy - v.y * wx));
	s1 *= detail;

	Pvector s2((u.y * wz - u.z * wy), (u.z * wx - u.x * wz), (u.x * wy - u.y * wx));
	s2 *= -detail;

	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); i++)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta * m_lookAhead);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// There is no faster way to do this.
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

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
		if (upos < 0 || vpos < 0 || upos > 1 || vpos > 1)
		{
			continue;
		}

		// A hit! A most palpable hit!
		// Compute distance to the three edges.
		Pvector uOffset = (un * (un * offset)) - offset;
		float uDistSquare = uOffset.Length2();

		Pvector vOffset = (vn * (vn * offset)) - offset;
		float vDistSquare = vOffset.Length2();

		Pvector substOffset((u + v) - offset);

		Pvector fOffset = (un * (un * substOffset)) - substOffset;
		float fDistSquare = fOffset.Length2();

		Pvector S;

		if (uDistSquare <= vDistSquare && uDistSquare <= fDistSquare)
		{
			S = uOffset;
		}
		else if (vDistSquare <= fDistSquare)
		{
			S = vOffset;
		}
		else 
		{
			S = fOffset;
		}

		S.normalize_safe();

		// We now have a vector3 to safety.
		float vm = particle.Velocity.Length();
		Pvector Vn = particle.Velocity / vm;

		// Blend S into V.
		Pvector tmp = (S * (magDelta / (t * t + m_epsilon))) + Vn;
		particle.Velocity = tmp * (vm / tmp.Length());
	}
}

void AvoidAction::ProcessTrianglePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	auto magDelta = m_magnitude * delta;

	// Compute the inverse matrix of the plane basis.
	auto& u = m_position->U();
	auto& v = m_position->V();

	// The normalized bases are needed inside the loop.
	auto un = u / m_position->OuterRadiusSquare();
	auto vn = v / m_position->InnerRadiusSquare();

	// f is the third (non-basis) triangle edge.
	Pvector fn(v - u);
	fn.normalize_safe();

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
		Pvector pnext(particle.Position + particle.Velocity * delta * m_lookAhead);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d.
		float distanceOld = particle.Position * m_position->Point2() + m_position->OuterRadius();
		float distanceNew = pnext * m_position->Point2() + m_position->OuterRadius();

		// Opposite signs if product < 0
		// There is no faster way to do this.
		if (distanceOld * distanceNew >= 0)
		{
			continue;
		}

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

		// A hit! A most palpable hit!
		// Compute distance to the three edges.
		Pvector uOffset = (un * (un * offset)) - offset;
		float uDistSquare = uOffset.Length2();

		Pvector vOffset = (vn * (vn * offset)) - offset;
		float vDistSquare = vOffset.Length2();

		Pvector substOffset(offset - u);

		Pvector fOffset = (fn * (fn * substOffset)) - substOffset;
		float fDistSquare = fOffset.Length2();

		Pvector S;

		if (uDistSquare <= vDistSquare && uDistSquare <= fDistSquare)
		{
			S = uOffset;
		}
		else if (vDistSquare <= fDistSquare)
		{
			S = vOffset;
		}
		else
		{
			S = fOffset;
		}

		S.normalize_safe();

		// We now have a vector3 to safety.
		float vm = particle.Velocity.Length();
		Pvector Vn = particle.Velocity / vm;

		// Blend S into V.
		Pvector tmp = (S * (magDelta / (t * t + m_epsilon))) + Vn;
		particle.Velocity = tmp * (vm / tmp.Length());
	}
}

void AvoidAction::ProcessSpherePosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	auto magDelta = m_magnitude * delta;
	float outerRadiusSquare = _sqr(m_position->OuterRadius());

	// See which particles are aimed toward the sphere.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// First do a ray-sphere intersection test and
		// see if it's soon enough.
		// Can I do this faster without t?
		float vm = particle.Velocity.Length();
		Pvector Vn = particle.Velocity / vm;

		Pvector l = m_position->Point1() - particle.Position;
		float v = l * Vn;

		float disc = outerRadiusSquare - (l * l) + v * v;

		if (disc < 0)
		{
			continue; // I'm not heading toward it.
		}

		// Compute length for second rejection test.
		float t = v - _sqrt(disc);

		if (t < 0 || t >(vm * m_lookAhead))
		{
			continue;
		}

		// Get a vector3 to safety.
		Pvector C = Vn ^ l;
		C.normalize_safe();

		Pvector S = Vn ^ C;

		// Blend S into V.
		Pvector tmp = (S * (magDelta / (t * t + m_epsilon))) + Vn;
		particle.Velocity = tmp * (vm / tmp.Length());
	}
}

void AvoidAction::ProcessDiscPosition(const ParticleEffect& effect, const float& delta, const float& maxLifeTime)
{
	auto magDelta = m_magnitude * delta;

	auto outerRadiusSquare = _sqr(m_position->OuterRadius());
	auto innerRadiusSquare = _sqr(m_position->InnerRadius());

	// See which particles bounce.
	for (u32 i = 0; i < effect.Count(); ++i)
	{
		Particle& particle = effect.Get(i);

		// See if particle's current and next positions cross plane.
		// If not, couldn't bounce, so keep going.
		Pvector pnext(particle.Position + particle.Velocity * delta * m_lookAhead);

		// p2 stores the plane normal (the a,b,c of the plane eqn).
		// Old and new distances: dist(p,plane) = n * p + d
		// radius1 stores -n*p, which is d. radius1Sqr stores d.
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

		// A hit! A most palpable hit!
		Pvector S = offset;
		S.normalize_safe();

		// We now have a vector3 to safety.
		float vm = particle.Velocity.Length();
		Pvector Vn = particle.Velocity / vm;

		// Blend S into V.
		Pvector tmp = (S * (magDelta / (t * t + m_epsilon))) + Vn;
		particle.Velocity = tmp * (vm / tmp.Length());
	}
}
