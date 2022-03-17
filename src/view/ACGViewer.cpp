/*
* HelloCAD a simple cad platform
*/

#include "ACGViewer.h"

#include "SceneCoordSys.h"

#include <acg/QtWidgets/QtExaminerViewer.hh>
#include <acg/Scenegraph/SeparatorNode.hh>

namespace view
{
	class ACGViewerPrivate
	{
	public:
		ACGViewerPrivate(){;}
		~ACGViewerPrivate();

		ACG::QtWidgets::QtExaminerViewer * _viewer;

		/// Scene graphs root node
		ACG::SceneGraph::SeparatorNode * _sceneRoot;

		/// Scene graphs root node
		ACG::SceneGraph::SeparatorNode * _objectRoot;

		/// Node for the coordinate system
		SceneCoordSys * _coordsysNode;
	};

	ACGViewerPrivate::~ACGViewerPrivate()
	{
		delete _coordsysNode;
		delete _objectRoot;
		delete _sceneRoot;
	}
}

using namespace view;

ACGViewer::ACGViewer(QWidget * parent /*= nullptr*/)
	:d_ptr(new ACGViewerPrivate())
{
	initScene();
}

ACGViewer::~ACGViewer()
{

}

void ACGViewer::addToViewer(ACG::SceneGraph::SeparatorNode * node)
{
	Q_D(ACGViewer);
	d->_objectRoot->push_back(node);
}

void ACGViewer::removeFromViewer(ACG::SceneGraph::SeparatorNode * node)
{
	Q_D(ACGViewer);
	ACG::SceneGraph::BaseNode::ChildIter it = d->_objectRoot->find(node);
	if (it != d->_objectRoot->childrenEnd())
	{
		d->_objectRoot->remove(it);
	}
}

void ACGViewer::initScene()
{
	Q_D(ACGViewer);
	//init widget
	{
		d->_viewer = new ACG::QtWidgets::QtExaminerViewer(this);

		QHBoxLayout * mainLayout = new QHBoxLayout();
		mainLayout->addWidget(d->_viewer);
		this->setLayout(mainLayout);
		mainLayout->setMargin(0);
	}

	//init viewer
	{
		d->_sceneRoot = new ACG::SceneGraph::SeparatorNode(0, "SceneGraph Root Node");
		d->_viewer->sceneGraph(d->_sceneRoot);
		d->_viewer->drawNow();

		d->_viewer->backgroundColor(ACG::Vec4f(0.3f, 0.6f, 0.3f, 1.0f));
		d->_viewer->applyOptions(d->_viewer->options() ^ ACG::QtWidgets::QtBaseViewer::ShowWheels);
		d->_viewer->projectionMode(ACG::QtWidgets::QtBaseViewer::ORTHOGRAPHIC_PROJECTION);
	}

	//coordinate system
	{
		d->_coordsysNode = new SceneCoordSys();
		d->_coordsysNode->addToScene(d->_sceneRoot);

	}

	//object root
	{
		d->_objectRoot = new ACG::SceneGraph::SeparatorNode(d->_sceneRoot, "Object Root Node");
	}
}

void ACGViewer::fitAll()
{
	Q_D(ACGViewer);
	d->_viewer->viewAll();
}

