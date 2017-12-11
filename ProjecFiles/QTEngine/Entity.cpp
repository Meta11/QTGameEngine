#include "Entity.h"
#include "Component.h"
#include "TypeDefs.h"

namespace Entities {

	Entity::Entity() {
		numComponents = 0;
	}

	bool Entity::initialize() {
		for (uint i = 0; i < numComponents; i++)
			if (!components[i]->initialize())
				return false;
		return true;
	}

	bool Entity::shutdown() {
		return true;
	}

	void Entity::addComponent(Component* component) {
		components[numComponents++] = component;
		component->parent = this;
	}

	void Entity::update() {
		for (uint i = 0; i < numComponents; i++)
			components[i]->update();
	}
}
