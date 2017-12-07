#pragma once
#include <QtCore\qobject.h>
#include <QtCore\qtimer.h>
#include <Renderer.h>
#include <Vector3D.h>
namespace Rendering { class Renderable; }

class MyGame : public QObject {
	Q_OBJECT

	QTimer myTimer;

	Rendering::Renderer renderer;
	Rendering::Renderable* shipInstance;
	Rendering::Renderable* lerpInstance;

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

