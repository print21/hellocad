/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "DataExport.h"

#include <common/DocumentBase.h>

namespace data
{
	class DocumentPrivate;
	class DATA_EXPORT Document : public common::DocumentBase
	{
		Q_OBJECT;
		CLASS_HEADER(data::Document);
	public:
		Document();
		~Document();

		const QString & documentName();

	protected:
		void setDocumentName(const QString & name);

	private:
		friend class Admin;
		Q_DECLARE_PRIVATE(Document);
		const QScopedPointer<DocumentPrivate> d_ptr;
	};
}



