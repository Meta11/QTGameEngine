#include "MyGame.h"
#include <cstdlib>
#include <Geometry.h>

using Rendering::Geometry;
using Math::Vector3D;

MyGame::MyGame() {
	Vector3D shipVertData[] = {
		Vector3D(+0.0f, +0.14142135623f, 1.0f),
		Vector3D(-0.1f, -0.1f, 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f)
	};
	memcpy(shipVerts, shipVertData, sizeof(shipVertData));

	ushort shipIndicesData[] = { 0,1,2 };
	memcpy(shipIndices, shipIndicesData, sizeof(shipIndicesData));
}

bool MyGame::initialize() {

	if (!renderer.initialize())
		return false;

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(update()));

	Geometry* shipGeometry = renderer.addGeometry(shipVerts, NUM_SHIP_VERTS, shipIndices, NUM_SHIP_INDICES, GL_TRIANGLES);
	shipRenderable = renderer.addRenderable(shipGeometry);
	shipRenderer.setData(shipRenderable);
	ship.addComponent(&shipRenderer);
	shipPhysics.velocity.x = 0.01f;
	ship.addComponent(&shipPhysics);

	if (!ship.initialize())
		return false;

	return true;
}

bool MyGame::shutdown() {
	return renderer.shutdown();
}

void MyGame::update() {
	ship.update();
	renderer.renderScene();
}

void MyGame::go() {
	myTimer.start(0);
}
