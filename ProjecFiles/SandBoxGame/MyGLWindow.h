#pragma once

#include <QtOpenGL\qgl.h>
#include <QtCore\qtimer.h>

class MyGLWindow : public QGLWidget {
	
	Q_OBJECT

	GLuint vertexBufferID;
	QTimer myTimer;

protected:
	void initializeGL();
	void paintGL();

private:
	void updateVelocity();
	void updateRotation();

private slots:
	void myUpdate();

public:
	bool initialize();
	bool shutDown();
};