#include "Renderer.h"

namespace Rendering {

	bool Renderer::initialize() {
		numGeometries = 0;
		numRenderables = 0;
		return true;
	}
	bool Renderer::shutdown() {
		return true;
	}

	Geometry* Renderer::addGeometry(Math::Vector3D* vertices, uint numVerts, ushort* indices, uint numIndices) {
		Geometry& g = geometries[numGeometries++];
		g.vertices = vertices;
		g.numVerts = numVerts;
		g.indices = indices;
		g.numIndices = numIndices;
		
		return &g;
	}

	Renderable* Renderer::addRenderable(Geometry* geometry) {
		Renderable& r = renderables[numRenderables++];
		r.what = geometry;
		return &r;
	}
}