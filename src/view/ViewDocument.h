/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include <common/DocumentBase.h>

namespace common
{
	class FeatureBase;
	class AttributeBase;
}

namespace view
{
	class ViewDocumentPrivate;
	class ViewDocument : public common::DocumentBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::ViewDocument);
	public:
		ViewDocument();
		~ViewDocument();

		void attach(const common::DocumentBase * dataDoc);

		const common::DocumentBase * dataDocument() const;

	protected:
		friend class Admin;
		Q_DECLARE_PRIVATE(ViewDocument);
		QScopedPointer<ViewDocumentPrivate> d_ptr;
	};
}
