#include "stdafx.h"
#include "BoxShapeController.h"

bool BoxShapeController::IsWithin(const ParticleShape& shape, const Pvector& vec) const
{
	return !((vec.x < shape.Point1.x) || (vec.x > shape.Point2.x) ||
		(vec.y < shape.Point1.y) || (vec.y > shape.Point2.y) ||
		(vec.z < shape.Point1.z) || (vec.z > shape.Point2.z));
}

ParticleShape BoxShapeController::Transform(const ParticleShape& shape, const Fmatrix& matrix)
{
	auto box_dest = (Fbox*)&shape.Point1;
	auto box_src = (Fbox*)&shape.Point1;

	box_dest->xform(*box_src, matrix);
	
	auto newShape = shape;

	newShape.Point1.x = box_dest->x1;
	newShape.Point2.x = box_dest->x2;
	newShape.Point1.y = box_dest->y1;
	newShape.Point2.y = box_dest->y2;
	newShape.Point1.z = box_dest->z1;
	newShape.Point2.z = box_dest->z2;

	return newShape;
}

ParticleShape BoxShapeController::TransformDir(const ParticleShape& shape, const Fmatrix& matrix)
{
	Fmatrix newMatrix = matrix;
	newMatrix.c.set(0, 0, 0);

	return Transform(shape, newMatrix);
}

Pvector BoxShapeController::GeneratePoint(const ParticleShape& shape) const
{
	auto x = shape.Point1.x + (shape.Point2.x - shape.Point1.x) * ::Random.randF();
	auto y = shape.Point1.y + (shape.Point2.y - shape.Point1.y) * ::Random.randF();
	auto z = shape.Point1.z + (shape.Point2.z - shape.Point1.z) * ::Random.randF();
	
	return Pvector(x, y, z);
}

ParticleShape BoxShapeController::Create(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    auto shape = ParticleShape();

    shape.Type = ParticleShapeType::Box;

	shape.Point1.x = p0 < p3 ? p0 : p3;
	shape.Point2.x = p0 < p3 ? p3 : p0;
	
	shape.Point1.y = p1 < p4 ? p1 : p4;
	shape.Point2.y = p1 < p4 ? p4 : p1;

	shape.Point1.z = p2 < p5 ? p2 : p5;
	shape.Point2.z = p2 < p5 ? p5 : p2;
    
    return shape;
}
