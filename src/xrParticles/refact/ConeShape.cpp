#include "stdafx.h"
#include "ConeShape.h"

ConeShape::ConeShape(const std::array<float, 9>& points)
{
    m_type = ParticleShapeType::Cone;

    // p2 is a vector3 from p1 to the other end of cylinder.
    // p1 is apex of cone.
    Pvector tmp(points[3], points[4], points[5]);

    m_point1 = Pvector(points[0], points[1], points[2]);
    m_point2 = tmp - m_point1;
    m_outerRadius = points[6] > points[7] ? points[6] : points[7];
    m_innerRadius = points[6] > points[7] ? points[7] : points[6];
    m_outerRadiusSquare = _sqr(m_outerRadius);


    // Given an arbitrary nonzero vector3 n, make two orthonormal
    // vectors u and v forming a frame [u,v,n.normalize()].
    m_point2.normalize_safe();
    float pt2sqrt = m_point2.Length2();

    // radius2Sqr stores 1 / (p2.p2)
    // XXX Used to have an actual if.
    m_innerRadiusSquare = pt2sqrt
        ? 1.0f / pt2sqrt
        : 0.f;

    // Find a vector3 orthogonal to n.
    Pvector basis(1.0f, 0.0f, 0.0f);

    if (_abs(basis * m_point2) > 0.999)
    {
        basis = Pvector(0.0f, 1.0f, 0.0f);
    }

    // Project away N component, normalize and cross to get
    // second orthonormal vector3.
    m_u = basis - m_point2 * (basis * m_point2);
    m_u.normalize_safe();

    m_v = m_point2 ^ m_u;
}

bool ConeShape::IsWithin(const Pvector& vec) const
{
    // This is painful and slow. Might be better to do quick
    // accept/reject tests.
    // Let p2 = vector3 from base to tip of the cylinder
    // x = vector3 from base to test point
    // x . p2
    // dist = ------ = projected distance of x along the axis
    // p2. p2 ranging from 0 (base) to 1 (tip)
    //
    // rad = x - dist * p2 = projected vector3 of x along the base
    // p1 is the apex of the cone.

    Pvector x(vec - m_point1);

    // Check axial distance InnerRadiusSquare stores 1 / (p2.p2)
    float dist = (m_point2 * x) * m_innerRadiusSquare;

    if (dist < 0.0f || dist > 1.0f)
    {
        return false;
    }

    // Check radial distance; scale radius along axis for cones 
    Pvector xrad = x - m_point2 * dist; // Radial component of x
    float sqr = xrad.Length2();

    return (sqr <= _sqr(dist * m_outerRadius) && sqr >= _sqr(dist * m_innerRadius));
}

Pvector ConeShape::GeneratePoint() const
{
    // For a cone, p2 is the apex of the cone.
    float dist = ::Random.randF(); // Distance between base and tip
    float theta = ::Random.randF() * 2.0f * float(M_PI); // Angle around axis

    // Distance from axis
    float r = m_innerRadius + ::Random.randF() * (m_outerRadius - m_innerRadius);
    float x = r * _cos(theta); // Weighting of each frame vector3
    float y = r * _sin(theta);

    x *= dist;
    y *= dist;

    return m_point1 + m_point2 * dist + m_u * x + m_v * y;
}

void ConeShape::Transform(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    matrix.transform_tiny(m_point1, sourceShape->Point1());
    matrix.transform_dir(m_point2, sourceShape->Point2());
    matrix.transform_dir(m_u, sourceShape->U());
    matrix.transform_dir(m_v, sourceShape->V());
}

void ConeShape::TransformDir(const ParticleShapeBase* sourceShape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(sourceShape, newMatrix);
}
