#pragma once
#include <Matrix3D.h>

namespace Rendering {
	class Geometry;
	class Renderable {
	public:
		const Geometry* what;
		Math::Matrix3D where;
	};
}


