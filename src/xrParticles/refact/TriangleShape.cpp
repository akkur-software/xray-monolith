#include "stdafx.h"
#include "TriangleShape.h"

TriangleShape::TriangleShape(const std::array<float, 9>& points)
{
	m_type = ParticleShapeType::Triangle;
	m_point1 = Pvector(points[0], points[1], points[2]);

	Pvector angle2 = Pvector(points[3], points[4], points[5]);
	Pvector angle3 = Pvector(points[6], points[7], points[8]);

	m_u = angle2 - m_point1;
	m_v = angle3 - m_point1;

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

bool TriangleShape::IsWithin(const Pvector& vec) const
{
    return false;
}

Pvector TriangleShape::GeneratePoint() const
{
	float randomValue1 = ::Random.randF();
	float randomValue2 = ::Random.randF();

	return (randomValue1 + randomValue2 < 1.0f)
		? m_point1 + m_u * randomValue1 + m_v * randomValue2
		: m_point1 + m_u * (1.0f - randomValue1) + m_v * (1.0f - randomValue2);
}

void TriangleShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
	matrix.transform_tiny(m_point1, sourceShape->Point1());
	matrix.transform_dir(m_point2, sourceShape->Point2());
	matrix.transform_dir(m_u, sourceShape->U());
	matrix.transform_dir(m_v, sourceShape->V());
}

void TriangleShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
	Fmatrix newMatrix = matrix;
	newMatrix.c.set(0, 0, 0);

	return Transform(sourceShape, newMatrix);
}
