#include "stdafx.h"
#include "BlobShapeController.h"

bool BlobShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    Pvector x(vec - shape.Point1);
    float Gx = expf(x.Length2() * shape.InnerRadiusSquare) * shape.InnerRadius;

    return (::Random.randF() < Gx);
}

ParticleShape BlobShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
    auto newShape = shape;
    matrix.transform_tiny(newShape.Point1, shape.Point1);

    return newShape;
}

ParticleShape BlobShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector BlobShapeController::GeneratePoint(const ParticleShape& shape) const
{
    auto x = shape.Point1.x + NRand(shape.OuterRadius);
    auto y = shape.Point1.y + NRand(shape.OuterRadius);
    auto z = shape.Point1.z + NRand(shape.OuterRadius);
    
    return Pvector(x, y, z);
}

ParticleShape BlobShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Blob;
    shape.OuterRadius = p3;

    float tmp = 1.f / shape.OuterRadius;

    shape.Point1 = Pvector(p0, p1, p2);    
    shape.InnerRadiusSquare = -0.5f * _sqr(tmp);
    shape.InnerRadius = ONEOVERSQRT2PI * tmp;

    return shape;
}
