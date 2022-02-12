/*
 *HelloCAD a simple cad platform
 */

#ifdef USE_VLD
#include <vld.h>
#endif

#include <QApplication>

#include "MainWindow.h"

#include <common/CommonAdmin.h>
#include <data/DataAdmin.h>
#include <view/ViewAdmin.h>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	common::Admin::init();
	data::Admin::init();
	view::Admin::init();

	hellocad::MainWindow mw;
	mw.show();

	app.exec();

	return 0;
}

