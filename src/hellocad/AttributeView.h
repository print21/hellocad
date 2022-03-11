/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QTreeWidget>

namespace common
{
	class FeatureBase;
}

namespace hellocad
{
	class AttributeViewPrivate;
	class AttributeView : public QTreeWidget
	{
		Q_OBJECT;
	public:
		explicit AttributeView(QWidget * parent = nullptr);
		~AttributeView();

	private:
		Q_DECLARE_PRIVATE(AttributeView);
		const QScopedPointer<AttributeViewPrivate> d_ptr;
	};
}

