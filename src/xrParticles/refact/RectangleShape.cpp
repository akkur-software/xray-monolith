#include "stdafx.h"
#include "RectangleShape.h"

RectangleShape::RectangleShape(const std::array<float, 9>& points)
{
	m_type = ParticleShapeType::Rectangle;

	m_point1 = Pvector(points[0], points[1], points[2]);
	m_u = Pvector(points[3], points[4], points[5]);
	m_v = Pvector(points[6], points[7], points[8]);

	// The rest of this is needed for bouncing.
	m_outerRadiusSquare = m_u.Length();
	Pvector tu = m_u / m_outerRadiusSquare;

	m_innerRadiusSquare = m_v.Length();
	Pvector tv = m_v / m_innerRadiusSquare;

	m_point2 = tu ^ tv; // This is the non-unit normal.
	m_point2.normalize_safe(); // Must normalize it.

	// radius1 stores the d of the plane eqn.
	m_outerRadius = -(m_point1 * m_point2);
}

bool RectangleShape::IsWithin(const Pvector& vec) const
{
    return false;
}

Pvector RectangleShape::GeneratePoint() const
{
	return m_point1 + m_u * ::Random.randF() + m_v * ::Random.randF();
}

void RectangleShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
	matrix.transform_tiny(m_point1, sourceShape->Point1());
	matrix.transform_dir(m_point2, sourceShape->Point2());
	matrix.transform_dir(m_u, sourceShape->U());
	matrix.transform_dir(m_v, sourceShape->V());
}

void RectangleShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
