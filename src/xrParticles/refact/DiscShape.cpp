#include "stdafx.h"
#include "DiscShape.h"

DiscShape::DiscShape(const std::array<float, 9>& points)
{
	m_type = ParticleShapeType::Disc;

	m_point1 = Pvector(points[0], points[1], points[2]); // Center point
	m_point2 = Pvector(points[3], points[4], points[5]); // Normal (not used in Within and Generate)

	m_point2.normalize_safe();

	m_outerRadius = points[6] > points[7] ? points[6] : points[7];
	m_innerRadius = points[6] > points[7] ? points[7] : points[6];

	// Find a vector3 orthogonal to n.
	Pvector basis(1.0f, 0.0f, 0.0f);

	if (_abs(basis * m_point2) > 0.999)
	{
		basis = Pvector(0.0f, 1.0f, 0.0f);
	}

	// Project away N component, normalize and cross to get second orthonormal vector3.
	m_u = basis - m_point2 * (basis * m_point2);
	m_u.normalize_safe();
	m_v = m_point2 ^ m_u;
	m_outerRadiusSquare = -(m_point1 * m_point2); // D of the plane eqn.
}

bool DiscShape::IsWithin(const Pvector& vec) const
{
    return false;
}

Pvector DiscShape::GeneratePoint() const
{
	float theta = ::Random.randF() * 2.0f * float(M_PI); // Angle around normal

	// Distance from center
	float r = m_innerRadius + ::Random.randF() * (m_outerRadius - m_innerRadius);
	float x = r * _cos(theta); // Weighting of each frame vector3
	float y = r * _sin(theta);

	return m_point1 + m_u * x + m_v * y;
}

void DiscShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
	matrix.transform_tiny(m_point1, sourceShape->Point1());
	matrix.transform_dir(m_point2, sourceShape->Point2());
	matrix.transform_dir(m_u, sourceShape->U());
	matrix.transform_dir(m_v, sourceShape->V());
}

void DiscShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
