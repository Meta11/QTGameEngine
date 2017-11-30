#include <GL\glew.h>
#include "MyGLWindow.h"
#include <QtCore\qdebug.h>
#include <QtGui\QKeyEvent>
#include <Vector3D.h>
#include <Matrix3D.h>
#include <Profiler.h>
#include <Profile.h>
#include <Clock.h>

using Math::Vector3D;
using Math::Matrix3D;
using Timing::Clock;

namespace {
	//Ponemos los vértices de la nave
	static Vector3D shipVerts[] = {
		Vector3D(+0.0f, +0.14142135623f, 1.0f),
		Vector3D(-0.1f, -0.1f, 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f)
	};

	static Vector3D boundaryVerts[] = {
		Vector3D(+0.0f, +1.0f, 1.0f),
		Vector3D(-1.0f, -0.0f, 1.0f),
		Vector3D(+0.0f, -1.0f, 1.0f),
		Vector3D(+1.0f, -0.0f, 1.0f)
	};

	GLushort boundaryElementVerts[] = { 0,1,1,2,2,3,3,0 };

	static const unsigned int NUM_SHIP_VERTS = sizeof(shipVerts) / sizeof(*shipVerts);
	static const unsigned int NUM_BOUNDARY_VERTS = sizeof(boundaryVerts) / sizeof(*boundaryVerts);

	GLuint shipVertexBufferID;
	GLuint boundaryVertexBufferID;
	GLuint boundaryElementsBufferID;

	Vector3D transformedVerts[NUM_SHIP_VERTS];
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
	glGenBuffers(1, &shipVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipVerts), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &boundaryVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaryVerts), boundaryVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &boundaryElementsBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundaryElementsBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boundaryElementVerts), boundaryElementVerts, GL_STATIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	//Tiempo de espera entre que se ejecuta un frame y el siguiente
	myTimer.start(0);
}

void MyGLWindow::update() {
	myClock.lap();
	profiler.newFrame();
	shipPosition = shipPosition + shipVelocity * myClock.lastLapTime();
	updateVelocity();
	updateRotation();
	checkForBoundaries();
}

void MyGLWindow::doGL() {

	glViewport(0, 0, width(), height());

	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, 0);
}

void MyGLWindow::draw() {

	Matrix3D tMatrix = Matrix3D::translate(shipPosition);
	Matrix3D rMatrix = Matrix3D::rotate(shipOrientation);
	float aspectRatio = static_cast<float> (width()) / height();
	Matrix3D sMatrix;
	
	if (aspectRatio > 1)
		sMatrix = Matrix3D::scale(1 / aspectRatio, 1);
	else
		sMatrix = Matrix3D::scale(1, aspectRatio);

	Matrix3D opMatrix;

	{
		PROFILE("Matrix Multiplication");
		opMatrix = tMatrix*sMatrix*rMatrix;
	}
	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_SHIP_VERTS; i++)
			transformedVerts[i] = opMatrix*shipVerts[i];
	}
	doGL();
}

void MyGLWindow::paintGL() {

	update();
	draw();
}

void MyGLWindow::myUpdate() {
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

	Vector3D acc(0, shipAcceleration*myClock.lastLapTime(), 0);
	Matrix3D rMatrix = Matrix3D::rotate(shipOrientation);
	if (GetAsyncKeyState(VK_UP)) {
		shipVelocity = shipVelocity + rMatrix*acc;
	}
	
}

void MyGLWindow::updateRotation() {

	const float angularVelocity = 2.0f*myClock.lastLapTime();

	if (GetAsyncKeyState(VK_RIGHT)) shipOrientation -= angularVelocity;
	if (GetAsyncKeyState(VK_LEFT)) shipOrientation += angularVelocity;
}

void MyGLWindow::checkForBoundaries() {

	for (int i = 0; i < NUM_BOUNDARY_VERTS; i++) {
		Vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];
		Vector3D& first = boundaryVerts[i % NUM_BOUNDARY_VERTS];
		Vector3D wall = second - first;
		Vector3D normal = wall.perpCcw();
		Vector3D vect = shipPosition - first;
		float result = normal.dot(vect);

		if (result < 0)
			qDebug() << "La nave está fuera de la pared" << (i + 1);
		else
			qDebug() << "";
	}
}