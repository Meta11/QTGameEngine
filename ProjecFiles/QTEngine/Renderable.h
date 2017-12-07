#pragma once
#include <Matrix3D.h>

namespace Rendering {
	class Geometry;
	class Renderable {
		friend class Renderer;
		const Geometry* what;
	public:
		Math::Matrix3D where;
	};
}


