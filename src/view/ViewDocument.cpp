/*
 *HelloCAD a simple cad platform
*/

#include "ViewDocument.h"

namespace view
{
	class ViewDocumentPrivate
	{
	public:
		ViewDocumentPrivate() { ; }
		~ViewDocumentPrivate() { ; }

		const common::DocumentBase * _dataDoc;
		//std::map<const common::FeatureBase *, ViewObjectBase*> _objectMap;
	};
}

using namespace view;

CLASS_SOURCE(view::ViewDocument)

ViewDocument::ViewDocument()
	:d_ptr(new ViewDocumentPrivate())
{

}

ViewDocument::~ViewDocument()
{

}

void ViewDocument::attach(const common::DocumentBase * dataDoc)
{
	Q_D(ViewDocument);
	Q_ASSERT(d->_dataDoc == nullptr);

	d->_dataDoc = dataDoc;
	Q_ASSERT(d->_dataDoc != nullptr);
	
	//connect signals
}

const common::DocumentBase * ViewDocument::dataDocument() const
{
	Q_D(const ViewDocument);
	return d->_dataDoc;
}


