#pragma once
#include "TypeDefs.h"

namespace Math { class Vector3D; }

namespace Rendering {
	class Geometry {
	public:
		const Math::Vector3D* vertices;
		uint numVerts;
		const ushort* indices;
		uint numIndices;
	};
}
