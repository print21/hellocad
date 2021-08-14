/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "DataExport.h"

#include <QObject>
#include <QScopedPointer>

namespace common
{
	class DocumentBase;
}

namespace data
{
	class AdminPrivate;
	class Admin : public QObject
	{
		Q_OBJECT
	public:
		~Admin();


		static void init();
		static Admin & instance();

		//! create document, if doc name is exist, doc rename with current time
		common::DocumentBase * createDocument(const QString & docName);

		//! activate document
		void activateDocument(const QString & docName);

		//! get current active document
		common::DocumentBase * activeDocument() const;

		//! get document by name
		common::DocumentBase * documentByName(const QString & docName);

		//! delete document
		void deleteDocument(const QString & docName);

		//! clear document
		void clearDocument();

	Q_SIGNALS:
		void signalNewDocument(const common::DocumentBase * doc);
		void signalDeleteDocument(const common::DocumentBase * doc);
		void signalActiveDocument(const common::DocumentBase * doc);
		void signalClearDocuments();

	protected:
		Admin();
		static QScopedPointer<Admin> _ptr;

	private:
		Q_DECLARE_PRIVATE(Admin);
		const QScopedPointer<AdminPrivate> d_ptr;
	};
}

