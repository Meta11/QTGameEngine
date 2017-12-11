#include "ControllerComponent.h"
#include <KeyInput.h>
#include <Entity.h>
#include <Vector3D.h>
#include <cmath>
#include <PhysicsComponent.h>
#include "MyMenuChoice.h"

namespace Entities {

	bool ControllerComponent::initialize() {

		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != 0;
	}
	void ControllerComponent::update() {
		const float ANGLUAR_VELOCITY = 2.0f;
		const float ACCELERATION = 0.5f;

		if (input.actionsHot(Input::RotateLeft))
			physics->angularVelocity = ANGLUAR_VELOCITY;
		else if (input.actionsHot(Input::RotateRight))
			physics->angularVelocity = -ANGLUAR_VELOCITY;
		else
			physics->angularVelocity = 0;
		if (input.actionsHot(Input::Accelerate)) {
			physics->acceleration.x = -sin(getParent()->orientation)*ACCELERATION;
			physics->acceleration.y =  cos(getParent()->orientation)*ACCELERATION;
		}
	}
}