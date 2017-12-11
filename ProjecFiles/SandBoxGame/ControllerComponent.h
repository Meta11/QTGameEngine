#pragma once
#include <Component.h>

namespace Entities {

	class PhysicsComponent;
	class ControllerComponent : public Component{
		PhysicsComponent* physics;
	public:
		bool initialize();
		void update();
	};
}


