/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include <common/FeatureBase.h>

#include <acg/Scenegraph/SeparatorNode.hh>

namespace view
{
	class ViewFeatureBase : public common::FeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::ViewFeatureBase);
	public:
		ViewFeatureBase();
		~ViewFeatureBase();

		virtual ACG::SceneGraph::SeparatorNode * rootNode() const = 0;
	};
}

