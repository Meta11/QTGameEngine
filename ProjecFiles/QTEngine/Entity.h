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
		float orientation;
		Entity();
		bool initialize();
		bool shutdown();
		void addComponent(Component* component);
		void update();
		template<class T>
		T* getComponent() const;
	};

	template<class T>
	T* Entity::getComponent() const {
		for (uint i = 0; i < numComponents; i++) {
			T* ret = dynamic_cast<T*>(components[i]);
			if (ret != nullptr)
				return ret;
		}
		return 0;
	}
}


