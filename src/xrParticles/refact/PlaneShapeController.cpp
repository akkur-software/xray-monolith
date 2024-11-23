#include "stdafx.h"
#include "PlaneShapeController.h"

bool PlaneShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    // Distance from plane = n * p + d, inside is the positive half-space.
    return vec * shape.Point2 >= -shape.OuterRadius;
}

ParticleShape PlaneShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;

    matrix.transform_tiny(newShape.Point1, shape.Point1);
    matrix.transform_dir(newShape.Point2, shape.Point2);

    newShape.OuterRadius = -(newShape.Point1 * newShape.Point2); // Outer radius stores the d of the plane eqn.    
    return newShape;
}

ParticleShape PlaneShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector PlaneShapeController::GeneratePoint(const ParticleShape& shape) const
{
    return Pvector(shape.Point1);
}

ParticleShape PlaneShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Plane;

    shape.Point1 = Pvector(p0, p1, p2);
    shape.Point2 = Pvector(p3, p4, p5);

    shape.Point2.normalize_safe(); // Must normalize it.    
    shape.OuterRadius = -(shape.Point1 * shape.Point2); // Outer radius stores the d of the plane eqn.
    
    return shape;
}
