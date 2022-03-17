/*
 *HelloCAD a simple cad platform
 */

#include "MainWindow.h"
#include "TreeView.h"
#include "AttributeView.h"

#include <common/DocumentBase.h>
#include <data/DataAdmin.h>
#include <data/DataDocument.h>
#include <view/ViewAdmin.h>
#include <view/ViewDocument.h>
#include <view/ACGViewer.h>

#include <QAction>
#include <QToolBar>
#include <QDebug>
#include <QTabWidget>
#include <QDockWidget>

namespace hellocad
{
	class MainWindowPrivate
	{
	public:
		MainWindowPrivate() { ; }
		~MainWindowPrivate() { ; }

		QString _currentDocName;
		QTabWidget* _centerView;

		TreeView* _treeView;

		AttributeView* _attributeView;

		static MainWindow* _mainWindow;
	};

	MainWindow * MainWindowPrivate::_mainWindow = nullptr;
}

using namespace hellocad;

MainWindow::MainWindow(QWidget * parent /*= nullptr*/)
	:d_ptr(new MainWindowPrivate())
{
	Q_ASSERT(MainWindowPrivate::_mainWindow == nullptr);
	MainWindowPrivate::_mainWindow = this;

	this->setWindowTitle(tr("HelloCAD a simple cad platform"));

	this->initToolBar();

	this->initWindow();

	this->resize(1024, 768);
}

MainWindow::~MainWindow()
{

}

MainWindow* MainWindow::mainWindow()
{
	return MainWindowPrivate::_mainWindow;
}

void MainWindow::initWindow()
{
	Q_D(MainWindow);
	d->_centerView = new QTabWidget(this);
	this->setCentralWidget(d->_centerView);

	{
		QDockWidget* dock = new QDockWidget(QString::fromUtf8("Project"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		d->_treeView = new TreeView(this);
		dock->setWidget(d->_treeView);

		this->addDockWidget(Qt::LeftDockWidgetArea, dock);
	}

	{
		QDockWidget* dock = new QDockWidget(QString::fromUtf8("Attribute"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		d->_attributeView = new AttributeView(this);
		dock->setWidget(d->_attributeView);

		this->addDockWidget(Qt::RightDockWidgetArea, dock);
	}
}

void MainWindow::initToolBar()
{
	{
		QToolBar * docTbr = this->addToolBar("Document");

		QAction * newDoc = docTbr->addAction("New Doc");
		
		docTbr->addSeparator();

		QAction * newCube = docTbr->addAction("Cube");

		docTbr->addSeparator();

		QAction* updateAct = docTbr->addAction("Update");

		connect(newDoc, SIGNAL(triggered()), this, SLOT(slotNewDocument()));
		connect(newCube, SIGNAL(triggered()), this, SLOT(slotCreateCube()));
		connect(updateAct, SIGNAL(triggered()), this, SLOT(slotUpdateDocument()));
	}
}

AttributeView* MainWindow::attributeView() const
{
	Q_D(const MainWindow);
	return d->_attributeView;
}

void MainWindow::slotNewDocument()
{
	data::Document * doc = dynamicCast<data::Document>(data::Admin::instance().createDocument("Document"));
	if (doc == nullptr)
	{
		qDebug() << "Create new document failed";
		return;
	}

	Q_D(MainWindow);
	d->_currentDocName = doc->documentName();

	view::Document * viewDoc = dynamicCast<view::Document>(view::Admin::instance().viewDocument(doc));
	d->_centerView->addTab(viewDoc->acgViewer(), doc->documentName());
}

void MainWindow::slotCreateCube()
{
	Q_D(MainWindow);
	data::Document* doc = dynamicCast<data::Document>(data::Admin::instance().documentByName(d->_currentDocName));
	if (doc == nullptr)
	{
		return;
	}

	doc->appendFeature("data::CubeFeature");
	doc->update();
}

void MainWindow::slotUpdateDocument()
{
	Q_D(MainWindow);

	common::DocumentBase * doc = data::Admin::instance().documentByName(d->_currentDocName);
	if (doc == nullptr)
	{
		return;
	}

	doc->update();
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


