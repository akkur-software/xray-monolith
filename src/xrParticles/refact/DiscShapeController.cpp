#include "stdafx.h"
#include "DiscShapeController.h"

bool DiscShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
    return false;
}

ParticleShape DiscShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
	auto newShape = shape;

	matrix.transform_tiny(newShape.Point1, shape.Point1);
	matrix.transform_dir(newShape.Point2, shape.Point2);
	matrix.transform_dir(newShape.U, shape.U);
	matrix.transform_dir(newShape.V, shape.V);

	return newShape;
}

ParticleShape DiscShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
    Fmatrix newMatrix = matrix;
    newMatrix.c.set(0, 0, 0);

    return Transform(shape, newMatrix);
}

Pvector DiscShapeController::GeneratePoint(const ParticleShape& shape) const
{
	float theta = ::Random.randF() * 2.0f * float(M_PI); // Angle around normal

	// Distance from center
	float r = shape.InnerRadius + ::Random.randF() * (shape.OuterRadius - shape.InnerRadius);
	float x = r * _cos(theta); // Weighting of each frame vector3
	float y = r * _sin(theta);

	return shape.Point1 + shape.U * x + shape.V * y;
}

ParticleShape DiscShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

	shape.Type = ParticleShapeType::Disc;

	shape.Point1 = Pvector(p0, p1, p2); // Center point
	shape.Point2 = Pvector(p3, p4, p5); // Normal (not used in Within and Generate)

	shape.Point2.normalize_safe();

	shape.OuterRadius = p6 > p7 ? p6 : p7;
	shape.InnerRadius = p6 > p7 ? p7 : p6;

	// Find a vector3 orthogonal to n.
	Pvector basis(1.0f, 0.0f, 0.0f);

	if (_abs(basis * shape.Point2) > 0.999)
	{
		basis = Pvector(0.0f, 1.0f, 0.0f);
	}

	// Project away N component, normalize and cross to get second orthonormal vector3.
	shape.U = basis - shape.Point2 * (basis * shape.Point2);
	shape.U.normalize_safe();
	shape.V = shape.Point2 ^ shape.U;
	shape.OuterRadiusSquare = -(shape.Point1 * shape.Point2); // D of the plane eqn.

    return shape;
}
