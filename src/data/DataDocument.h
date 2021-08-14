/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "DataExport.h"

#include <common/DocumentBase.h>

namespace data
{
	class DataDocumentPrivate;
	class DataDocument : public common::DocumentBase
	{
		Q_OBJECT
		CLASS_HEADER(data::DataDocument)
	public:
		DataDocument();
		~DataDocument();

		const QString & documentName();

	protected:
		void setDocumentName(const QString & name);

	private:
		friend class Admin;
		Q_DECLARE_PRIVATE(DataDocument);
		const QScopedPointer<DataDocumentPrivate> d_ptr;
	};
}



