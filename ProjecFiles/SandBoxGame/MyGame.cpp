#include "MyGame.h"
#include <cstdlib>
#include <Geometry.h>
#include <GameClock.h>
#include <MyMenuChoice.h>
#include <KeyInput.h>
#include <MyKeyMapper.h>

using Rendering::Geometry;
using Math::Vector3D;

bool MyGame::initialize() {

	if (!renderer.initialize())
		return false;
	if (!input.intialize(&keyMapper, Input::MyMenuChoice::MAX))
		return false;
	if (!gameClock.initialize())
		return false;
	if (!connect(&myTimer, SIGNAL(timeout()), this, SLOT(update())))
		return false;
	if (!initializeShip())
		return false;
	if (!sendBoundaryDataToRenderer())
		return false;

	return true;
}

bool MyGame::shutdown() {
	bool good = true;
	good &= ship.shutdown();
	good &= gameClock.shutdown();
	good &= input.shutdown();
	good &= renderer.shutdown();

	return good;
}

void MyGame::update() {
	gameClock.newFrame();
	input.update();
	ship.update();
	renderer.renderScene();	
}

void MyGame::go() {
	myTimer.start(0);
}

bool MyGame::initializeShip() {

	Vector3D shipVertData[] = {
		Vector3D(+0.0f, +0.14142135623f, 1.0f),
		Vector3D(-0.1f, -0.1f, 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f)
	};
	ushort shipIndicesData[] = { 0,1,2 };

	if (sizeof(shipVertData) / sizeof(*shipVertData) != NUM_SHIP_VERTS)
		return false;
	if (sizeof(shipIndicesData) / sizeof(*shipIndicesData) != NUM_SHIP_INDICES)
		return false;

	memcpy(shipVerts, shipVertData, sizeof(shipVertData));
	memcpy(shipIndices, shipIndicesData, sizeof(shipIndicesData));

	ship.addComponent(&shipController);
	ship.addComponent(&shipPhysics);
	shipBoundaryHandler.setData(boundaryVerts, NUM_BOUNDARY_VERTS);
	ship.addComponent(&shipBoundaryHandler);

	Geometry* shipGeometry = renderer.addGeometry(shipVerts, NUM_SHIP_VERTS, shipIndices, NUM_SHIP_INDICES, GL_TRIANGLES);
	shipRenderable = renderer.addRenderable(shipGeometry);
	shipRenderer.setData(shipRenderable);
	ship.addComponent(&shipRenderer);

	return ship.initialize();
}

bool MyGame::sendBoundaryDataToRenderer() {

	Vector3D boundaryVertsData[] = {
		Vector3D(+0.0f, +1.0f, 1.0f),
		Vector3D(-1.0f, -0.0f, 1.0f),
		Vector3D(+0.0f, -1.0f, 1.0f),
		Vector3D(+1.0f, -0.0f, 1.0f)
	};

	GLushort boundaryIndicesVerts[] = { 0,1,1,2,2,3,3,0 };

	if (sizeof(boundaryVertsData) / sizeof(*boundaryVertsData) != NUM_BOUNDARY_VERTS)
		return false;
	if (sizeof(boundaryIndicesVerts) / sizeof(*boundaryIndicesVerts) != NUM_BOUNDARY_INDICES)
		return false;

	memcpy(boundaryVerts, boundaryVertsData, sizeof(boundaryVertsData));
	memcpy(boundaryIndices, boundaryIndicesVerts, sizeof(boundaryIndicesVerts));

	Geometry* boundaryGeometry = renderer.addGeometry(boundaryVerts, NUM_BOUNDARY_VERTS, boundaryIndices, NUM_BOUNDARY_INDICES, GL_LINES);
	shipRenderable = renderer.addRenderable(boundaryGeometry);
	
	return true;
}