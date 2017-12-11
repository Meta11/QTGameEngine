#pragma once
#include "Component.h"
#include "Vector3D.h"
#include "TypeDefs.h"


namespace Entities {
	class PhysicsComponent;
	class __declspec(dllexport) BoundaryHandlerComponent : public Component {
		Math::Vector3D* boundaryVerts;
		uint NUM_BOUNDARY_VERTS;
		PhysicsComponent* physics;
		Math::Vector3D oldShipPosition;
	public:
		BoundaryHandlerComponent();
		bool initialize();
		void setData(Math::Vector3D* boundaryVerts, uint numBoundaryVerts);
		void update();
	};
}