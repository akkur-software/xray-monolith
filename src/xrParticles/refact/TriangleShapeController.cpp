#include "stdafx.h"
#include "TriangleShapeController.h"

bool TriangleShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    return false;
}

ParticleShape TriangleShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
	auto newShape = shape;

	matrix.transform_tiny(newShape.Point1, shape.Point1);
	matrix.transform_dir(newShape.Point2, shape.Point2);
	matrix.transform_dir(newShape.U, shape.U);
	matrix.transform_dir(newShape.V, shape.V);
	
	return newShape;
}

ParticleShape TriangleShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
	Fmatrix newMatrix = matrix;
	newMatrix.c.set(0, 0, 0);

	return Transform(shape, newMatrix);
}

Pvector TriangleShapeController::GeneratePoint(const ParticleShape& shape) const
{
	float randomValue1 = ::Random.randF();
	float randomValue2 = ::Random.randF();

	Pvector vec = (randomValue1 + randomValue2 < 1.0f)
		? shape.Point1 + shape.U * randomValue1 + shape.V * randomValue2
		: shape.Point1 + shape.U * (1.0f - randomValue1) + shape.V * (1.0f - randomValue2);
	
	return vec;
}

ParticleShape TriangleShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

	shape.Type = ParticleShapeType::Triangle;

	shape.Point1 = Pvector(p0, p1, p2);

	Pvector angle2 = Pvector(p3, p4, p5);
	Pvector angle3 = Pvector(p6, p7, p8);

	shape.U = angle2 - shape.Point1;
	shape.V = angle3 - shape.Point1;

	// The rest of this is needed for bouncing.
	shape.OuterRadiusSquare = shape.U.Length();
	Pvector tu = shape.U / shape.OuterRadiusSquare;
	shape.InnerRadiusSquare = shape.V.Length();
	Pvector tv = shape.V / shape.InnerRadiusSquare;

	shape.Point2 = tu ^ tv; // This is the non-unit normal.
	shape.Point2.normalize_safe(); // Must normalize it.

	// radius1 stores the d of the plane eqn.
	shape.OuterRadius = -(shape.Point1 * shape.Point2);
    
    return shape;
}
