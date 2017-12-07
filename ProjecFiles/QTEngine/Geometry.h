#pragma once
#include "TypeDefs.h"

namespace Math { struct Vector3D; }

namespace Rendering {
	class Geometry {
		friend class Renderer;
		const Math::Vector3D* vertices;
		uint numVerts;
		const ushort* indices;
		uint numIndices;
		GLenum renderMode;
	};
}
