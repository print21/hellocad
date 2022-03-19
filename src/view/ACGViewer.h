/*
* HelloCAD a simple cad platform
*/

#pragma once

#include "ViewExport.h"

#include <QWidget>
#include <QScopedPointer>

namespace ACG
{
	namespace SceneGraph
	{
		class SeparatorNode;
	}
}

namespace view
{
	class ACGViewerPrivate;
	class VIEW_EXPORT ACGViewer : public QWidget
	{
		Q_OBJECT
	public:
		ACGViewer(QWidget * parent = nullptr);
		~ACGViewer();

		void addToViewer(ACG::SceneGraph::SeparatorNode * node);
		void removeFromViewer(ACG::SceneGraph::SeparatorNode * node);

		void fitAll();

		void updateViewer();

	protected:
		void initScene();

	private:
		Q_DECLARE_PRIVATE(ACGViewer);
		const QScopedPointer<ACGViewerPrivate> d_ptr;
	};
}
