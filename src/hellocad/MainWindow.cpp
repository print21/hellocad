/*
 *HelloCAD a simple cad platform
 */

#include "MainWindow.h"

#include <view/ACGViewer.h>

namespace hellocad
{
	class MainWindowPrivate
	{
	public:
		MainWindowPrivate() { ; }
		~MainWindowPrivate() { ; }

		view::ACGViewer * _viewer;
	};
}

using namespace hellocad;

MainWindow::MainWindow(QWidget * parent /*= nullptr*/)
	:d_ptr(new MainWindowPrivate())
{
	this->setWindowTitle(tr("HelloCAD a simple cad platform"));

	Q_D(MainWindow);
	d->_viewer = new view::ACGViewer(this);
	this->setCentralWidget(d->_viewer);
}

MainWindow::~MainWindow()
{

}
