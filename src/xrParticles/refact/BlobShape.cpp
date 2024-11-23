#include "stdafx.h"
#include "BlobShape.h"

BlobShape::BlobShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Blob;
    m_outerRadius = points[3];

    float tmp = 1.f / m_outerRadius;

    m_point1 = Pvector(points[0], points[1], points[2]);
    m_innerRadiusSquare = -0.5f * _sqr(tmp);
    m_innerRadius = ONEOVERSQRT2PI * tmp;
}

bool BlobShape::IsWithin(const Pvector& vec) const
{
    Pvector x(vec - m_point1);
    float Gx = expf(x.Length2() * m_innerRadiusSquare) * m_innerRadius;

    return (::Random.randF() < Gx);
}

void BlobShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
}

void BlobShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}

Pvector BlobShape::GeneratePoint() const
{
    auto x = m_point1.x + NRand(m_outerRadius);
    auto y = m_point1.y + NRand(m_outerRadius);
    auto z = m_point1.z + NRand(m_outerRadius);
    
    return Pvector(x, y, z);
}
