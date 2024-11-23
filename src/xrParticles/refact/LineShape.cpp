#include "stdafx.h"
#include "LineShape.h"

LineShape::LineShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Line;

    m_point1 = Pvector(points[0], points[1], points[2]);
    m_point2 = Pvector(points[3], points[4], points[5]) - m_point1; // Point2 is vector3 from Point1 to other endpoint.
}

bool LineShape::IsWithin(const Pvector& vec) const
{
    return false;
}

void LineShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
    matrix.transform_dir(m_point2, sourceShape->Point2());
}

void LineShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}

Pvector LineShape::GeneratePoint() const
{
    return m_point1 + m_point2 * ::Random.randF();
}
