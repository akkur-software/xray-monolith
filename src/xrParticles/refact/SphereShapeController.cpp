#include "stdafx.h"
#include "SphereShapeController.h"

bool SphereShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    Pvector newVec(vec - shape.Point1);
    float sqr = newVec.Length2();

    return sqr <= shape.OuterRadiusSquare && sqr >= shape.InnerRadiusSquare;
}

ParticleShape SphereShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;
    matrix.transform_tiny(newShape.Point1, shape.Point1);
    
    return newShape;
}

ParticleShape SphereShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector SphereShapeController::GeneratePoint(const ParticleShape& shape) const
{
    // Place on [-1..1] sphere
    auto randomVec = Pvector(::Random.randF(), ::Random.randF(), ::Random.randF());
    auto halfVec = Pvector(0.5f, 0.5f, 0.5f);

    auto vec = randomVec - halfVec;
    vec.normalize_safe();

    // Scale unit sphere pos by [0..r] and translate (should distribute as r^2 law)
    return shape.OuterRadius == shape.InnerRadius
        ? shape.Point1 + vec * shape.OuterRadius
        : shape.Point1 + vec * (shape.InnerRadius + ::Random.randF() * (shape.OuterRadius - shape.InnerRadius));
}

ParticleShape SphereShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();
    
    shape.Type = ParticleShapeType::Sphere;

    shape.Point1 = Pvector(p0, p1, p2);

    shape.OuterRadius = p3 > p4 ? p3 : p4;
    shape.InnerRadius = p3 > p4 ? p4 : p3;

    shape.OuterRadiusSquare = shape.OuterRadius * shape.OuterRadius;
    shape.InnerRadiusSquare = shape.InnerRadius * shape.InnerRadius;

    return shape;
}
