/*
 *HelloCAD a simple cad platform
 */

#ifdef USE_VLD
#include <vld.h>
#endif

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	hellocad::MainWindow mw;
	mw.show();

	app.exec();

	return 0;
}

