#pragma once
#include <QtOpenGL\qgl.h>
#include <QtCore\qtimer.h>

class MyGLWindow : public QGLWidget {
	
	Q_OBJECT

	QTimer myTimer;

protected:
	void initializeGL();
	void paintGL();

private:
	void updateVelocity();
	void updateRotation();
	void update();
	void doGL();
	void draw();
	void checkForBoundaries();

private slots:
	void myUpdate();

public:
	bool initialize();
	bool shutDown();
};