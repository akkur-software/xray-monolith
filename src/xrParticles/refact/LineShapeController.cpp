#include "stdafx.h"
#include "LineShapeController.h"

bool LineShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    return false;
}

ParticleShape LineShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;

    matrix.transform_tiny(newShape.Point1, shape.Point1);
    matrix.transform_dir(newShape.Point2, shape.Point2);
    
    return newShape;
}

ParticleShape LineShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector LineShapeController::GeneratePoint(const ParticleShape& shape) const
{
    return shape.Point1 + shape.Point2 * ::Random.randF();
}

ParticleShape LineShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Line;
    shape.Point1 = Pvector(p0, p1, p2);    
    shape.Point2 = Pvector(p3, p4, p5) - shape.Point1; // // Point2 is vector3 from Point1 to other endpoint.

    return shape;
}
