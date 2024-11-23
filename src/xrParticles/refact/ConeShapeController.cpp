#include "stdafx.h"
#include "ConeShapeController.h"

bool ConeShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
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

    Pvector x(vec - shape.Point1);

    // Check axial distance InnerRadiusSquare stores 1 / (p2.p2)
    float dist = (shape.Point2 * x) * shape.InnerRadiusSquare;

    if (dist < 0.0f || dist > 1.0f)
    {
        return false;
    }

    // Check radial distance; scale radius along axis for cones 
    Pvector xrad = x - shape.Point2 * dist; // Radial component of x
    float sqr = xrad.Length2();

    return (sqr <= _sqr(dist * shape.OuterRadius) && sqr >= _sqr(dist * shape.InnerRadius));
}

ParticleShape ConeShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;

    matrix.transform_tiny(newShape.Point1, shape.Point1);
    matrix.transform_dir(newShape.Point2, shape.Point2);
    matrix.transform_dir(newShape.U, shape.U);
    matrix.transform_dir(newShape.V, shape.V);

    return newShape;
}

ParticleShape ConeShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector ConeShapeController::GeneratePoint(const ParticleShape& shape) const
{
    // For a cone, p2 is the apex of the cone.
    float dist = ::Random.randF(); // Distance between base and tip
    float theta = ::Random.randF() * 2.0f * float(M_PI); // Angle around axis

    // Distance from axis
    float r = shape.InnerRadius + ::Random.randF() * (shape.OuterRadius - shape.InnerRadius);
    float x = r * _cos(theta); // Weighting of each frame vector3
    float y = r * _sin(theta);

    x *= dist;
    y *= dist;

    return shape.Point1 + shape.Point2 * dist + shape.U * x + shape.V * y;
}

ParticleShape ConeShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Cone;

    // p2 is a vector3 from p1 to the other end of cylinder.
    // p1 is apex of cone.
    Pvector tmp(p3, p4, p5);

    shape.Point1 = Pvector(p0, p1, p2);
    shape.Point2 = tmp - shape.Point1;
    shape.OuterRadius = p6 > p7 ? p6 : p7;
    shape.InnerRadius = p6 > p7 ? p7 : p6;
    shape.OuterRadiusSquare = _sqr(shape.OuterRadius);


    // Given an arbitrary nonzero vector3 n, make two orthonormal
    // vectors u and v forming a frame [u,v,n.normalize()].
    shape.Point2.normalize_safe();
    float pt2sqrt = shape.Point2.Length2();

    // radius2Sqr stores 1 / (p2.p2)
    // XXX Used to have an actual if.
    shape.InnerRadiusSquare = pt2sqrt
        ? 1.0f / pt2sqrt
        : 0.f;

    // Find a vector3 orthogonal to n.
    Pvector basis(1.0f, 0.0f, 0.0f);

    if (_abs(basis * shape.Point2) > 0.999)
    {
        basis = Pvector(0.0f, 1.0f, 0.0f);
    }

    // Project away N component, normalize and cross to get
    // second orthonormal vector3.
    shape.U = basis - shape.Point2 * (basis * shape.Point2);
    shape.U.normalize_safe();

    shape.V = shape.Point2 ^ shape.U;

    return shape;
}
