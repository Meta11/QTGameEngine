#pragma once
#include <QtCore\qobject.h>
#include <QtCore\qtimer.h>
#include <Renderer.h>
#include <Vector3D.h>
#include <Entity.h>
#include "ControllerComponent.h"
#include <BoundaryHandlerComponent.h>
#include <PhysicsComponent.h>
#include <RendererComponent.h>
#include "MyKeyMapper.h"

namespace Rendering { class Renderable; }

class MyGame : public QObject {
	Q_OBJECT

	QTimer myTimer;

	Input::MyKeyMapper keyMapper;
	Entities::Entity ship;
	Entities::RendererComponent shipRenderer;
	Entities::PhysicsComponent shipPhysics;
	Entities::ControllerComponent shipController;
	Entities::BoundaryHandlerComponent shipBoundaryHandler;

	Rendering::Renderer renderer;
	Rendering::Renderable* shipRenderable;
	Rendering::Renderable* lerpRenderable;

	static const uint NUM_SHIP_VERTS = 3;
	Math::Vector3D shipVerts[NUM_SHIP_VERTS];
	static const uint NUM_SHIP_INDICES = 3;
	ushort shipIndices[NUM_SHIP_INDICES];

	static const uint NUM_BOUNDARY_VERTS = 4;
	Math::Vector3D boundaryVerts[NUM_BOUNDARY_VERTS];
	static const uint NUM_BOUNDARY_INDICES = 8;
	ushort boundaryIndices[NUM_BOUNDARY_INDICES];

	bool initializeShip();
	bool sendBoundaryDataToRenderer();
private slots:
	void update();
public:
	bool initialize();
	bool shutdown();
	void go();

};

