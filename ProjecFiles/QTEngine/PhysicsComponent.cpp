#include "PhysicsComponent.h"
#include "Entity.h"

namespace Entities {

	void PhysicsComponent::update() {
		getParent()->position += velocity;
	}
}