/*
 *HelloCAD a simple cad platform
*/

#include "ViewDocument.h"
#include "ACGViewer.h"

namespace view
{
	class DocumentPrivate
	{
	public:
		DocumentPrivate() : _dataDoc(nullptr) { ; }
		~DocumentPrivate() { ; }

		const common::DocumentBase * _dataDoc;
		QScopedPointer<ACGViewer> _acgViewer;
	};
}

using namespace view;

CLASS_SOURCE(view::Document);

Document::Document()
	:d_ptr(new DocumentPrivate())
{
	Q_D(Document);
	d->_acgViewer.reset(new ACGViewer());
}

Document::~Document()
{

}

ACGViewer* Document::acgViewer() const
{
	Q_D(const Document);
	return d->_acgViewer.get();
}

void Document::attach(const common::DocumentBase * dataDoc)
{
	Q_D(Document);
	Q_ASSERT(d->_dataDoc == nullptr);

	d->_dataDoc = dataDoc;
	Q_ASSERT(d->_dataDoc != nullptr);
	
	//connect signals
}

const common::DocumentBase * Document::dataDocument() const
{
	Q_D(const Document);
	return d->_dataDoc;
}


