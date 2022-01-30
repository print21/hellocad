/*
* HelloCAD a simple cad platform
*/

#pragma once

#include "ViewExport.h"

#include <QObject>

namespace common
{
	class DocumentBase;
}

namespace view
{
	class AdminPrivate;
	class VIEW_EXPORT Admin : public QObject
	{
		Q_OBJECT
	public:
		~Admin();

		static void init();
		static Admin & instance();

		common::DocumentBase* viewDocument(const common::DocumentBase * dataDoc) const;

	protected:
		Admin();
		static QScopedPointer<Admin> _ptr;

	protected Q_SLOTS:
		void slotNewDocument(const common::DocumentBase* doc);
		void slotDeleteDocument(const common::DocumentBase* doc);

	private:
		Q_DECLARE_PRIVATE(Admin);
		const QScopedPointer<AdminPrivate> d_ptr;
	};
}


