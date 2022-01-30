/*
 *HelloCAD a simple cad platform
*/

#include "DataDocument.h"

namespace data
{
	class DocumentPrivate
	{
	public:
		DocumentPrivate() { ; }
		~DocumentPrivate() { ; }

		QString _docName;
	};
}

using namespace data;

CLASS_SOURCE(data::Document);

Document::Document()
	: d_ptr(new DocumentPrivate())
{
}

Document::~Document()
{
}

void Document::setDocumentName(const QString & name)
{
	Q_D(Document);
	d->_docName = name;
}

const QString & Document::documentName()
{
	Q_D(Document);
	return d->_docName;
}
