#include "stdafx.h"
#include "PointShapeController.h"

bool PointShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    return false;
}

ParticleShape PointShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;
    matrix.transform_tiny(newShape.Point1, shape.Point1);
    
    return newShape;
}

ParticleShape PointShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector PointShapeController::GeneratePoint(const ParticleShape& shape) const
{
    return Pvector(shape.Point1);
}

ParticleShape PointShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Point;
    shape.Point1 = Pvector(p0, p1, p2);

    return shape;
}
