#pragma once
#include <QtCore\qobject.h>
#include <QtCore\qtimer.h>
#include <Renderer.h>
#include <Vector3D.h>
#include <Entity.h>
#include <PhysicsComponent.h>
#include <RendererComponent.h>

namespace Rendering { class Renderable; }

class MyGame : public QObject {
	Q_OBJECT

	QTimer myTimer;

	Entities::Entity ship;
	Entities::RendererComponent shipRenderer;
	Entities::PhysicsComponent shipPhysics;

	Rendering::Renderer renderer;
	Rendering::Renderable* shipRenderable;
	Rendering::Renderable* lerpRenderable;

	static const uint NUM_SHIP_VERTS = 3;
	Math::Vector3D shipVerts[NUM_SHIP_VERTS];
	static const uint NUM_SHIP_INDICES = 3;
	ushort shipIndices[NUM_SHIP_INDICES];
private slots:
	void update();
public:
	MyGame();
	bool initialize();
	bool shutdown();
	void go();

};

