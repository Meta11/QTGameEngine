#include "BoundaryHandlerComponent.h"
#include <Entity.h>
#include <PhysicsComponent.h>

using Math::Vector3D;

namespace Entities {

	BoundaryHandlerComponent::BoundaryHandlerComponent() {
		boundaryVerts = nullptr;
		physics = nullptr;
	}

	bool BoundaryHandlerComponent::initialize() {
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != nullptr && boundaryVerts != nullptr;
	}

	void BoundaryHandlerComponent::setData(Math::Vector3D* boundaryVerts, uint numBoundaryVerts) {
		this->boundaryVerts = boundaryVerts;
		NUM_BOUNDARY_VERTS = numBoundaryVerts;
	}

	void BoundaryHandlerComponent::update() {
		for (uint i = 0; i < NUM_BOUNDARY_VERTS; i++) {
			Vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];
			Vector3D& first = boundaryVerts[i % NUM_BOUNDARY_VERTS];
			Vector3D wall = second - first;
			Vector3D normal = wall.perpCcw();
			Vector3D vect = getParent()->position - first;
			float result = normal.dot(vect);

			if (result < 0) {
				physics->velocity = physics->velocity - 2 * physics->velocity.projectOnto(normal);
				getParent()->position = oldShipPosition;
			}
			oldShipPosition = getParent()->position;
		}
	}
}