#pragma once
#include <TypeDefs.h>
#include <Vector3D.h>

namespace Entities {

	class Component;
	class __declspec(dllexport) Entity {
		static const uint NUM_MAX_COMPONENTS = 10;
		Component* components[NUM_MAX_COMPONENTS];
		uint numComponents;
	public:
		Math::Vector3D position;
		Entity();
		bool initialize();
		bool shutdown();
		void addComponent(Component* component);
		void update();
	};
}


