#include "stdafx.h"
#include "SphereShape.h"

SphereShape::SphereShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Sphere;
    m_point1 = Pvector(points[0], points[1], points[2]);

    m_outerRadius = points[3] > points[4] ? points[3] : points[4];
    m_innerRadius = points[3] > points[4] ? points[4] : points[3];

    m_outerRadiusSquare = m_outerRadius * m_outerRadius;
    m_innerRadiusSquare = m_innerRadius * m_innerRadius;
}

bool SphereShape::IsWithin(const Pvector& vec) const
{
    Pvector newVec(vec - m_point1);
    float sqr = newVec.Length2();

    return sqr <= m_outerRadiusSquare && sqr >= m_innerRadiusSquare;
}

Pvector SphereShape::GeneratePoint() const
{
    // Place on [-1..1] sphere
    auto randomVec = Pvector(::Random.randF(), ::Random.randF(), ::Random.randF());
    auto halfVec = Pvector(0.5f, 0.5f, 0.5f);

    auto vec = randomVec - halfVec;
    vec.normalize_safe();

    // Scale unit sphere pos by [0..r] and translate (should distribute as r^2 law)
    return m_outerRadius == m_innerRadius
        ? m_point1 + vec * m_outerRadius
        : m_point1 + vec * (m_innerRadius + ::Random.randF() * (m_outerRadius - m_innerRadius));
}

void SphereShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
}

void SphereShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
