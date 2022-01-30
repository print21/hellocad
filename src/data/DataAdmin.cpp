/*
 *HelloCAD a simple cad platform
*/

#include "DataAdmin.h"

#include "DataDocument.h"
#include "DataFeatureBase.h"
#include "DataCubeFeature.h"

namespace data
{
	QScopedPointer<Admin> Admin::_ptr(nullptr);

	class AdminPrivate
	{
	public:
		AdminPrivate()
		{
			;
		}
		~AdminPrivate() { ; }

		std::map<QString, Document *> _docMap;

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

	data::Document::init();
	data::FeatureBase::init();
	data::CubeFeature::init();
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

	QObject * newPtr = core::ClassFactory::createObject("data::Document");
	Document* newDoc = qobject_cast<Document *>(newPtr);
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

	Document * doc = it->second;

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

