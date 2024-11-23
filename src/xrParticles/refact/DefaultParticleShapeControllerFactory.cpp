#include "BoxShapeController.h"
#include "PointShapeController.h"
#include "LineShapeController.h"
#include "PlaneShapeController.h"
#include "TriangleShapeController.h"
#include "SphereShapeController.h"
#include "CylinderShapeController.h"
#include "ConeShapeController.h"
#include "RectangleShapeController.h"
#include "BlobShapeController.h"
#include "DiscShapeController.h"
#include "DefaultParticleShapeControllerFactory.h"

IParticleShapeController* DefaultParticleShapeControllerFactory::CreateController(const ParticleShapeType& shapeType)
{
	switch (shapeType)
	{
	case ParticleShapeType::Box: return xr_new<BoxShapeController>();
	case ParticleShapeType::Point: return xr_new<PointShapeController>();
	case ParticleShapeType::Line: return xr_new<LineShapeController>();
	case ParticleShapeType::Plane: return xr_new<PlaneShapeController>();
	case ParticleShapeType::Triangle: return xr_new<TriangleShapeController>();
	case ParticleShapeType::Sphere: return xr_new<SphereShapeController>();
	case ParticleShapeType::Cylinder: return xr_new<CylinderShapeController>();
	case ParticleShapeType::Cone: return xr_new<ConeShapeController>();
	case ParticleShapeType::Rectangle: return xr_new<RectangleShapeController>();
	case ParticleShapeType::Blob: return xr_new<BlobShapeController>();
	case ParticleShapeType::Disc: return xr_new<DiscShapeController>();
	default: return nullptr;
	}
}
