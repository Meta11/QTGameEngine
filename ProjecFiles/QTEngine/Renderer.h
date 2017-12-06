#pragma once
#include "TypeDefs.h"
#include "Geometry.h"
#include "Renderable.h"

namespace Math { class Vector3D; }

namespace Rendering {
	class Renderer {
		static const uint NUM_MAX_GEOMETRIES = 10;
		Geometry geometries[NUM_MAX_GEOMETRIES];
		uint numGeometries;
		uint numRenderables;
		static const uint NUM_MAX_RENDERABLES = 10;
		Renderable renderables[NUM_MAX_RENDERABLES];
	public:
		bool initialize();
		bool shutdown();
		Geometry* addGeometry(Math::Vector3D* vertices, uint numVerts, ushort* indices, uint numIndices);
		Renderable* addRenderable(Geometry* geometry);
	};
}