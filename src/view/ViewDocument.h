/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "ViewExport.h"

#include <common/DocumentBase.h>

namespace common
{
	class DocumentBase;
	class FeatureBase;
	class AttributeBase;
}

namespace view
{
	class ACGViewer;

	class DocumentPrivate;
	class VIEW_EXPORT Document : public common::DocumentBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::Document);
	public:
		Document();
		~Document();

		void attach(const common::DocumentBase * dataDoc);

		const common::DocumentBase * dataDocument() const;

		ACGViewer* acgViewer() const;

	protected Q_SLOTS:
		void slotAppendDataFeature(const common::DocumentBase* caller, const common::FeatureBase* obj);
		void slotRemoveDataFeature(const common::DocumentBase* caller, const common::FeatureBase* obj);
		void slotAfterDataUpdate(const common::DocumentBase* caller);

	protected:
		friend class Admin;
		Q_DECLARE_PRIVATE(Document);
		QScopedPointer<DocumentPrivate> d_ptr;
	};
}
