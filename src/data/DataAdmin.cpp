/*
 *HelloCAD a simple cad platform
*/

#include "DataAdmin.h"

#include "DataDocument.h"

namespace data
{
	class DataDocument;

	QScopedPointer<Admin> Admin::_ptr(nullptr);

	class AdminPrivate
	{
	public:
		AdminPrivate()
		{
			;
		}
		~AdminPrivate() { ; }

		std::map<QString, DataDocument *> _docMap;

		void clearDocument()
		{
			for (auto it : _docMap)
			{
				delete it.second;
			}

			_docMap.clear();
		}
	};
}

using namespace data;

Admin::Admin()
	:d_ptr(new AdminPrivate())
{

}

Admin::~Admin()
{
	Q_D(Admin);
	d->clearDocument();
}

void Admin::init()
{
	Q_ASSERT(Admin::_ptr == nullptr);
	Admin::_ptr.reset(new Admin());
}

Admin & Admin::instance()
{
	return *(Admin::_ptr);
}

common::DocumentBase * Admin::createDocument(const QString & docName)
{
	Q_D(Admin);
	auto it = d->_docMap.find(docName);
	if (it != d->_docMap.end())
	{
		qDebug() << "Document(" << docName << ") already exist.";
		return nullptr;
	}

	QObject * newPtr = core::ClassFactory::createObject("ibe::postdata::DataDocument");
	DataDocument * newDoc = qobject_cast<DataDocument *>(newPtr);
	if (newDoc == nullptr)
	{
		return nullptr;
	}

	newDoc->setDocumentName(docName);
	d->_docMap.emplace(docName, newDoc);

	emit signalNewDocument(newDoc);

	return newDoc;
}

void Admin::deleteDocument(const QString & docName)
{
	Q_D(Admin);
	auto it = d->_docMap.find(docName);
	if (it == d->_docMap.end())
	{
		return;
	}

	DataDocument * doc = it->second;

	emit signalDeleteDocument(doc);

	d->_docMap.erase(it);
	delete doc;
}

common::DocumentBase * Admin::documentByName(const QString & docName)
{
	Q_D(Admin);
	auto it = d->_docMap.find(docName);
	if (it != d->_docMap.end())
	{
		return it->second;
	}

	qDebug() << "Document (" << docName << ") not existed";
	return nullptr;
}

