/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include "ViewFeatureBase.h"

namespace view
{
	class ViewPolyFeature : public ViewFeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::ViewPolyFeature);
	public:
		ViewPolyFeature();
		~ViewPolyFeature();

		virtual ACG::SceneGraph::SeparatorNode* rootNode() const override;

	protected:
		virtual void attachDataFeature(const common::FeatureBase* data) override;

		virtual bool excute() override;

	protected:
		ACG::SceneGraph::SeparatorNode* _rootNode;
	};
}

