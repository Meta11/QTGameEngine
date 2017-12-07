#pragma once
#include <QtOpenGL\qgl.h>
#include "TypeDefs.h"
#include "Geometry.h"
#include "Renderable.h"

namespace Math { struct Vector3D; }

namespace Rendering {

	class __declspec(dllexport) Renderer : public QGLWidget {
		static const uint NUM_MAX_GEOMETRIES = 10;
		Geometry geometries[NUM_MAX_GEOMETRIES];
		uint numGeometries;
		static const uint NUM_MAX_RENDERABLES = 10;
		Renderable renderables[NUM_MAX_RENDERABLES];
		uint numRenderables;
		static const uint MAX_BUFFER_SIZE = 1024;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		static const uint MAX_VERTS = 10;
	protected:
		void initializeGL();
		void paintEvent();
		void paintGL();
	public:
		bool initialize();
		bool shutdown();
		Geometry* addGeometry(Math::Vector3D* vertices, uint numVerts, ushort* indices, uint numIndices, GLenum renderMode);
		Renderable* addRenderable(Geometry* geometry);
		void renderScene();
	};
}