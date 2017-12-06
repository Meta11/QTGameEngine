#include "MyGame.h"
#include <Renderable.h>

bool MyGame::initialize() {
	Geometry* shipGeometry = renderer.addGeometry(shipVerts, numShipVerts, shipIndices, numShipIndices);
	shipInstance = renderer.addRenderable(shipGeometry);
	lerpInstance = renderer.addRenderable(shipGeometry);
}

void MyGame::update() {
	shipInstance->where = Math::Matrix3D::translate(shipPosition);
	lerpInstance->where = Math::Matrix3D::translate(lerpPosition);
}
