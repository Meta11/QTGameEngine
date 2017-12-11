#pragma once


namespace Entities {

	class Entity;
	class __declspec(dllexport) Component {
		friend class Entity;
		Entity* parent;

	public:
		Entity* getParent() const { return this->parent; }
		virtual bool initialize() { return true; }
		virtual bool shutdown() { return true; }
		virtual void update() {}
	};
}


