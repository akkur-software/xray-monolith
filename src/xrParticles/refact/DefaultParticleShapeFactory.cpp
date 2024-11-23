#include "BoxShape.h"
#include "PointShape.h"
#include "LineShape.h"
#include "PlaneShape.h"
#include "TriangleShape.h"
#include "SphereShape.h"
#include "CylinderShape.h"
#include "ConeShape.h"
#include "RectangleShape.h"
#include "BlobShape.h"
#include "DiscShape.h"
#include "DefaultParticleShapeFactory.h"

ParticleShapeBase* DefaultParticleShapeFactory::CreateShape(const ParticleShapeType& shapeType, const std::array<float, 9>& points)
{
	switch (shapeType)
	{
		case ParticleShapeType::Box: return xr_new<BoxShape>(points);
		case ParticleShapeType::Point: return xr_new<PointShape>(points);
		case ParticleShapeType::Line: return xr_new<LineShape>(points);
		case ParticleShapeType::Plane: return xr_new<PlaneShape>(points);
		case ParticleShapeType::Triangle: return xr_new<TriangleShape>(points);
		case ParticleShapeType::Sphere: return xr_new<SphereShape>(points);
		case ParticleShapeType::Cylinder: return xr_new<CylinderShape>(points);
		case ParticleShapeType::Cone: return xr_new<ConeShape>(points);
		case ParticleShapeType::Rectangle: return xr_new<RectangleShape>(points);
		case ParticleShapeType::Blob: return xr_new<BlobShape>(points);
		case ParticleShapeType::Disc: return xr_new<DiscShape>(points);
		default: return nullptr;
	}
}
