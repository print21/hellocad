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

		void hide();

		void show();

		bool visible() const;

	protected:
		virtual void attachDataFeature(const common::FeatureBase* data);
		virtual bool excute() override;

	protected Q_SLOTS:
		void slotDataFeatureStatusChanged(const common::FeatureBase* sender, STATUS st, bool value);

	protected:
		friend class view::Document;
		const common::FeatureBase* _data;
	};
}

