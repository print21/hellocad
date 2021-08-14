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
		AdminPrivate() : _activeDocument(nullptr)
		{
			;
		}
		~AdminPrivate() { ; }

		std::map<QString, DataDocument *> _docMap;
		DataDocument * _activeDocument;

		void clearDocument()
		{
			for (auto it : _docMap)
			{
				delete it.second;
			}

			_docMap.clear();
			_activeDocument = nullptr;
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

	QObject * newPtr = common::ClassFactory::createObject("ibe::postdata::DataDocument");
	DataDocument * newDoc = qobject_cast<DataDocument *>(newPtr);
	if (newDoc == nullptr)
	{
		return nullptr;
	}

	newDoc->setDocumentName(docName);
	d->_docMap.emplace(docName, newDoc);

	d->_activeDocument = newDoc;

	emit signalNewDocument(newDoc);

	emit signalActiveDocument(newDoc);

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
	if (d->_activeDocument == doc)
	{
		d->_activeDocument = nullptr;

		emit signalActiveDocument(nullptr);
	}

	emit signalDeleteDocument(doc);

	d->_docMap.erase(it);
	delete doc;
}

void Admin::activateDocument(const QString & docName)
{
	Q_D(Admin);
	if (d->_activeDocument != nullptr &&
		d->_activeDocument->documentName() == docName)
	{
		return;
	}

	auto it = d->_docMap.find(docName);
	if (it == d->_docMap.end())
	{
		d->_activeDocument = nullptr;
	}
	else
	{
		d->_activeDocument = it->second;
	}

	emit signalActiveDocument(d->_activeDocument);
}

common::DocumentBase * Admin::activeDocument() const
{
	Q_D(const Admin);
	return d->_activeDocument;
}

void Admin::clearDocument()
{
	Q_D(Admin);
	d->clearDocument();

	emit signalClearDocuments();
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

