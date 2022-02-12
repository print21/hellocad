/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QTreeWidget>

namespace common
{
	class DocumentBase;
}

namespace hellocad
{
	class TreeView : public QTreeWidget
	{
		Q_OBJECT;
	public:
		explicit TreeView(QWidget* parent = nullptr);
		~TreeView();

	protected Q_SLOTS:
		void slotNewDocument(const common::DocumentBase* doc);
	};
}
