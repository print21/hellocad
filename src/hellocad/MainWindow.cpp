/*
 *HelloCAD a simple cad platform
 */

#include "MainWindow.h"

#include <common/DocumentBase.h>
#include <data/DataAdmin.h>
#include <data/DataDocument.h>
#include <view/ViewAdmin.h>
#include <view/ViewDocument.h>
#include <view/ACGViewer.h>

#include <QAction>
#include <QToolBar>
#include <QDebug>

namespace hellocad
{
	class MainWindowPrivate
	{
	public:
		MainWindowPrivate() { ; }
		~MainWindowPrivate() { ; }

		QString _currentDocName;
	};
}

using namespace hellocad;

MainWindow::MainWindow(QWidget * parent /*= nullptr*/)
	:d_ptr(new MainWindowPrivate())
{
	this->setWindowTitle(tr("HelloCAD a simple cad platform"));

	this->initToolBar();

	this->resize(1024, 768);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initToolBar()
{
	{
		QToolBar * docTbr = this->addToolBar("Document");

		QAction * newDoc = docTbr->addAction("New Doc");
		
		docTbr->addSeparator();

		QAction * newCube = docTbr->addAction("Cube");

		connect(newDoc, SIGNAL(triggered()), this, SLOT(slotNewDocument()));
		connect(newCube, SIGNAL(triggered()), this, SLOT(slotCreateCube()));
	}
}

void MainWindow::slotNewDocument()
{
	data::Document * doc = dynamicCast<data::Document>(data::Admin::instance().createDocument("document"));
	if (doc == nullptr)
	{
		qDebug() << "Create new document failed";
	}

	Q_D(MainWindow);
	d->_currentDocName = doc->documentName();

	view::Document * viewDoc = dynamicCast<view::Document>(view::Admin::instance().viewDocument(doc));
	this->setCentralWidget(viewDoc->acgViewer());
}

void MainWindow::slotCreateCube()
{
	qDebug() << "New cube";
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	Q_D(MainWindow);
	data::Document* doc = dynamicCast<data::Document>(data::Admin::instance().documentByName(d->_currentDocName));
	if (doc != nullptr)
	{
		data::Admin::instance().deleteDocument(d->_currentDocName);
	}

	QMainWindow::closeEvent(event);
}


