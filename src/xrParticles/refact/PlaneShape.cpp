#include "stdafx.h"
#include "PlaneShape.h"

PlaneShape::PlaneShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Plane;

    m_point1 = Pvector(points[0], points[1], points[2]);
    m_point2 = Pvector(points[3], points[4], points[5]);

    m_point2.normalize_safe(); // Must normalize it.    
    m_outerRadius = -(m_point1 * m_point2); // Outer radius stores the d of the plane eqn.
}

bool PlaneShape::IsWithin(const Pvector& vec) const
{
    // Distance from plane = n * p + d, inside is the positive half-space.
    return vec * m_point2 >= -m_outerRadius;
}

Pvector PlaneShape::GeneratePoint() const
{
    return Pvector(m_point1);
}

void PlaneShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
    matrix.transform_dir(m_point2, sourceShape->Point2());

    // Outer radius stores the d of the plane eqn.  
    m_outerRadius = -(m_point1 * m_point2);   
}

void PlaneShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
