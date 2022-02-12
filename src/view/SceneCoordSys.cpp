/*
* HelloCAD a simple cad platform
*/

#include "SceneCoordSys.h"

#include <ACG/Scenegraph/SeparatorNode.hh>
#include <ACG/Scenegraph/CoordsysNode.hh>
#include <ACG/Scenegraph/MaterialNode.hh>

using namespace view;

SceneCoordSys::SceneCoordSys()
	:_rootNode(nullptr), _coordsysMaterial(nullptr), _coordsysNode(nullptr)
{
	;
}

SceneCoordSys::~SceneCoordSys()
{
	delete _rootNode;
	delete _coordsysNode;
	delete _coordsysMaterial;
}

void SceneCoordSys::addToScene(ACG::SceneGraph::SeparatorNode * root)
{
	if (_rootNode)
	{
		Q_ASSERT(false);
	}

	_rootNode = new ACG::SceneGraph::SeparatorNode(root, "Coordsys Root Node");
	// Coordsys rendering nodes
	_coordsysMaterial = new ACG::SceneGraph::MaterialNode(_rootNode, "Coordsys Material Node");
	_coordsysNode = new ACG::SceneGraph::CoordsysNode(_coordsysMaterial, "Coordsys Node");
	_coordsysNode->setTraverseMode(ACG::SceneGraph::BaseNode::NodeFirst | ACG::SceneGraph::BaseNode::SecondPass);
}
