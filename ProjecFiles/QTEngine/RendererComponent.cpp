#include "RendererComponent.h"
#include "Renderable.h"
#include "Entity.h"
#include "Matrix3D.h"

namespace Entities {

	void RendererComponent::setData(Rendering::Renderable* renderable) {
		this->renderable = renderable;
	}

	void RendererComponent::update() {
		renderable->where = Math::Matrix3D::translate(getParent()->position) *
			                Math::Matrix3D::rotate(getParent()->orientation);
	}
}