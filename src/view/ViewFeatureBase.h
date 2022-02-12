/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "ViewExport.h"

#include <common/FeatureBase.h>

namespace ACG
{
	namespace SceneGraph
	{
		class SeparatorNode;
	}
}

namespace view
{
	class Document;

	class VIEW_EXPORT ViewFeatureBase : public common::FeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::ViewFeatureBase);
	public:
		ViewFeatureBase();
		~ViewFeatureBase();

		virtual ACG::SceneGraph::SeparatorNode* rootNode() const = 0;

	protected:
		virtual void attachDataFeature(const common::FeatureBase* data);
		virtual bool excute() override;

	protected:
		friend class view::Document;
		const common::FeatureBase* _data;
	};
}

