#include "stdafx.h"
#include "ParticleShapeBase.h"

ParticleShapeBase::ParticleShapeBase() : 
	m_type(ParticleShapeType::Unknown),
	m_point1(Pvector(0.f, 0.f, 0.f)),
	m_point2(Pvector(0.f, 0.f, 0.f)),
	m_u(Pvector(0.f, 0.f, 0.f)),
	m_v(Pvector(0.f, 0.f, 0.f)),
	m_outerRadius(0.f),
	m_innerRadius(0.f),
	m_outerRadiusSquare(0.f),
	m_innerRadiusSquare(0.f)
{
}

ParticleShapeType ParticleShapeBase::Type() const
{
	return m_type;
}

Pvector ParticleShapeBase::Point1() const
{
	return m_point1;
}

Pvector ParticleShapeBase::Point2() const
{
	return m_point2;
}

Pvector ParticleShapeBase::U() const
{
	return m_u;
}

Pvector ParticleShapeBase::V() const
{
	return m_v;
}

float ParticleShapeBase::OuterRadius() const
{
	return m_outerRadius;
}

float ParticleShapeBase::InnerRadius() const
{
	return m_innerRadius;
}

float ParticleShapeBase::OuterRadiusSquare() const
{
	return m_outerRadiusSquare;
}

float ParticleShapeBase::InnerRadiusSquare() const
{
	return m_innerRadiusSquare;
}

constexpr size_t ParticleShapeBase::SizeOf()
{
	return 
		sizeof(m_type) +
		sizeof(m_point1) + 
		sizeof(m_point2) + 
		sizeof(m_u) + 
		sizeof(m_v) + 
		sizeof(m_outerRadius) + 
		sizeof(m_innerRadius) + 
		sizeof(m_outerRadiusSquare) + 
		sizeof(m_innerRadiusSquare);
}
