#pragma once
#include "Component.h"
#include <Vector3D.h>

namespace Entities {

	class __declspec(dllexport) PhysicsComponent : public Component {
		
	public:
		Math::Vector3D velocity;
		void update();
	};

}

