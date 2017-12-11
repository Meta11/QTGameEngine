#pragma once
#include <Component.h>

namespace Rendering { class Renderable; }

namespace Entities {

	class __declspec(dllexport) RendererComponent : public Component{
	
		Rendering::Renderable* renderable;
	public:
		void setData(Rendering::Renderable* renderable);
		void update();
	};
}

