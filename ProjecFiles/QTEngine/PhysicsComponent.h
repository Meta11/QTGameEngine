#pragma once
#include "Component.h"
#include <Vector3D.h>

namespace Entities {

	class __declspec(dllexport) PhysicsComponent : public Component {
		
	public:
		PhysicsComponent() { angularVelocity = 0; }
		float angularVelocity;
		Math::Vector3D velocity;
		Math::Vector3D acceleration;
		void update();
	};

}

