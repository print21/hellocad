/*
 *HelloCAD a simple cad platform
*/

#include "ViewAdmin.h"
#include "ViewDocument.h"

#include <data/DataAdmin.h>

namespace view
{
	QScopedPointer<Admin> Admin::_ptr(nullptr);

	class AdminPrivate
	{
	public:
		AdminPrivate() { ; }
		~AdminPrivate() { ; }

		std::map<const common::DocumentBase *, QScopedPointer<Document>> _docMap;
	};
}

using namespace view;

Admin::Admin()
	:d_ptr(new AdminPrivate())
{
	connect(&(data::Admin::instance()), &data::Admin::signalNewDocument, this, &Admin::slotNewDocument);
	connect(&(data::Admin::instance()), &data::Admin::signalDeleteDocument, this, &Admin::slotDeleteDocument);
}

Admin::~Admin()
{
}

void Admin::init()
{
	Q_ASSERT(Admin::_ptr == nullptr);
	Admin::_ptr.reset(new Admin());

	//connect signals
}

Admin & Admin::instance()
{
	return *(Admin::_ptr);
}

common::DocumentBase* Admin::viewDocument(const common::DocumentBase* dataDoc) const
{
	Q_D(const Admin);
	auto it = d->_docMap.find(dataDoc);
	if (it == d->_docMap.end())
	{
		return nullptr;
	}

	return it->second.get();
}

void Admin::slotNewDocument(const common::DocumentBase* doc)
{
	Q_ASSERT(viewDocument(doc) == nullptr);

	view::Document* viewDoc = new view::Document();
	viewDoc->attach(doc);

	Q_D(Admin);
	d->_docMap.emplace(doc, viewDoc);
}

void Admin::slotDeleteDocument(const common::DocumentBase* doc)
{
	Q_ASSERT(viewDocument(doc) != nullptr);

	Q_D(Admin);
	auto it = d->_docMap.find(doc);
	d->_docMap.erase(it);
}
