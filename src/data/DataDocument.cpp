/*
 *HelloCAD a simple cad platform
*/

#include "DataDocument.h"

namespace data
{
	class DataDocumentPrivate
	{
	public:
		DataDocumentPrivate() { ; }
		~DataDocumentPrivate() { ; }

		QString _docName;
	};
}

using namespace data;

DataDocument::DataDocument()
	: d_ptr(new DataDocumentPrivate())
{
}

DataDocument::~DataDocument()
{
}

void DataDocument::setDocumentName(const QString & name)
{
	Q_D(DataDocument);
	d->_docName = name;
}

const QString & DataDocument::documentName()
{
	Q_D(DataDocument);
	return d->_docName;
}
