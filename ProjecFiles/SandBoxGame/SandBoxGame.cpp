#include <QtWidgets\qapplication.h>
#include <QtWidgets\qwidget.h>
#include <QtCore\qdebug.h>
#include "MyGLWindow.h"

int main(int argc, char* argv[]) {

	QApplication application(argc, argv);
	MyGLWindow myGLWindow;
	if (!myGLWindow.initialize())
		return -1;

	myGLWindow.show();

	int errorCode = application.exec();
	if (!myGLWindow.shutDown())
		errorCode |= 1;

	return errorCode;
}