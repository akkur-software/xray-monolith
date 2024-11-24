#include "stdafx.h"
#include "PointShape.h"

PointShape::PointShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Point;
    m_point1 = Pvector(points[0], points[1], points[2]);
}

bool PointShape::IsWithin(const Pvector& vec) const
{
    return false;
}

Pvector PointShape::GeneratePoint() const
{
    return Pvector(m_point1);
}

void PointShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
}

void PointShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
