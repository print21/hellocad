/*
 *HelloCAD a simple cad platform
 */

#include "ViewPolyFeature.h"
#include "ViewDocument.h"
#include "ACGViewer.h"

#include <data/DataFeatureBase.h>
#include <acg/Scenegraph/SeparatorNode.hh>

using namespace view;

CLASS_SOURCE(view::ViewPolyFeature);

ViewPolyFeature::ViewPolyFeature()
	:_rootNode(nullptr)
{
}

ViewPolyFeature::~ViewPolyFeature()
{
	if (_rootNode != nullptr)
	{
		delete _rootNode;
	}
}

void ViewPolyFeature::attachDataFeature(const common::FeatureBase* data)
{
	ViewFeatureBase::attachDataFeature(data);

	if (_rootNode == nullptr)
	{
		_rootNode = new ACG::SceneGraph::SeparatorNode(nullptr, std::to_string(data->id()));
	}
}

ACG::SceneGraph::SeparatorNode* ViewPolyFeature::rootNode() const
{
	return _rootNode;
}

bool ViewPolyFeature::excute()
{
	if (_rootNode->parent() == nullptr)
	{
		view::Document* viewDoc = dynamicCast<view::Document>(this->document());
		Q_ASSERT(viewDoc != nullptr);

		ACGViewer* viewer = viewDoc->acgViewer();
		viewer->addToViewer(_rootNode);
	}

	const data::FeatureBase* data = dynamicCast<data::FeatureBase>(this->_data);
	if (data == nullptr)
	{
		return false;
	}

	return false;
}

