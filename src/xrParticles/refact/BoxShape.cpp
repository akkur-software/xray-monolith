#include "stdafx.h"
#include "BoxShape.h"

BoxShape::BoxShape(const std::array<float, 9>& points)
{
	m_type = ParticleShapeType::Box;

	m_point1.x = points[0] < points[3] ? points[0] : points[3];
	m_point2.x = points[0] < points[3] ? points[3] : points[0];

	m_point1.y = points[1] < points[4] ? points[1] : points[4];
	m_point2.y = points[1] < points[4] ? points[4] : points[1];

	m_point1.z = points[2] < points[5] ? points[2] : points[5];
	m_point2.z = points[2] < points[5] ? points[5] : points[2];
}

bool BoxShape::IsWithin(const Pvector& vec) const
{
	return !((vec.x < m_point1.x) || (vec.x > m_point2.x) ||
		(vec.y < m_point1.y) || (vec.y > m_point2.y) ||
		(vec.z < m_point1.z) || (vec.z > m_point2.z));
}

Pvector BoxShape::GeneratePoint() const
{
	auto x = m_point1.x + (m_point2.x - m_point1.x) * ::Random.randF();
	auto y = m_point1.y + (m_point2.y - m_point1.y) * ::Random.randF();
	auto z = m_point1.z + (m_point2.z - m_point1.z) * ::Random.randF();

	return Pvector(x, y, z);
}

void BoxShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{	
	auto box_src = (Fbox*)&sourceShape->Point1();
	auto box_dest = box_src;

	box_dest->xform(*box_src, matrix);

	m_point1.x = box_dest->x1;
	m_point2.x = box_dest->x2;
	m_point1.y = box_dest->y1;
	m_point2.y = box_dest->y2;
	m_point1.z = box_dest->z1;
	m_point2.z = box_dest->z2;
}

void BoxShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
	Fmatrix newMatrix = matrix;
	newMatrix.c.set(0, 0, 0);

	return Transform(sourceShape, newMatrix);
}
