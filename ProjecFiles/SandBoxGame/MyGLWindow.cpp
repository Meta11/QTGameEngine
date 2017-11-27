#include <GL\glew.h>
#include "MyGLWindow.h"
#include <QtCore\qdebug.h>
#include <QtGui\QKeyEvent>
#include <Vector3D.h>
#include <Matrix3D.h>
#include <Profiler.h>
#include <Clock.h>

using Math::Vector3D;
using Math::Matrix3D;
using Timing::Clock;

namespace {
	//Ponemos los vértices
	static Vector3D verts[] = {
		Vector3D(+0.0f, +0.14142135623f, 1.0f),
		Vector3D(-0.1f, -0.1f, 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f)
	};

	static const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);

	Vector3D shipPosition;
	Vector3D shipVelocity;
	float shipAcceleration = 0.5f;
	float shipOrientation = 0.0f;
	Clock myClock;

}

void MyGLWindow::initializeGL() {
	//Inicializamos el glew
	glewInit();

	//Generamos el array buffer
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	//Llenamos el buffer con la data del array
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), NULL, GL_DYNAMIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	//Tiempo de espera entre que se ejecuta un frame y el siguiente
	myTimer.start(0);
}

void MyGLWindow::paintGL() {

	glViewport(0, 0, width(), height());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	Vector3D transformedVerts[NUM_VERTS];
	Matrix3D tMatrix = Matrix3D::translate(shipPosition);
	Matrix3D rMatrix = Matrix3D::rotate(shipOrientation);
	
	Matrix3D opMatrix = tMatrix*rMatrix;
	for (unsigned int i = 0; i < NUM_VERTS; i++)
		transformedVerts[i] = opMatrix*verts[i];

	qDebug() << transformedVerts[0].x << " " << transformedVerts[0].y << " " << transformedVerts[0].z;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGLWindow::myUpdate() {

	myClock.lap();
	shipPosition = shipPosition + shipVelocity * myClock.timeElapsedLastFrame();
	updateVelocity();
	updateRotation();
	repaint();
}

bool MyGLWindow::initialize() {
	bool ret = true;
	profiler.initialize("profiles.csv");
	ret &= myClock.initialize();
	return ret;
}

bool MyGLWindow::shutDown() {
	bool ret = true;
	profiler.shutdown();
	ret &= myClock.shutdown();
	return ret;
}

void MyGLWindow::updateVelocity() {

	Vector3D acc(0, shipAcceleration*myClock.timeElapsedLastFrame(), 0);
	Matrix3D rMatrix = Matrix3D::rotate(shipOrientation);
	if (GetAsyncKeyState(VK_UP)) {
		shipVelocity = shipVelocity + rMatrix*acc;
	}
	
}

void MyGLWindow::updateRotation() {

	const float angularVelocity = 2.0f*myClock.timeElapsedLastFrame();

	if (GetAsyncKeyState(VK_RIGHT)) shipOrientation -= angularVelocity;
	if (GetAsyncKeyState(VK_LEFT)) shipOrientation += angularVelocity;
}