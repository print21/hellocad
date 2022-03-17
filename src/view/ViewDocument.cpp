/*
 *HelloCAD a simple cad platform
*/

#include "ViewDocument.h"
#include "ACGViewer.h"
#include "ViewPolyFeature.h"

#include <common/DocumentBase.h>
#include <common/FeatureBase.h>
#include <common/AttributeBase.h>

#include <data/DataFeatureBase.h>

namespace view
{
	class DocumentPrivate
	{
	public:
		DocumentPrivate() : _dataDoc(nullptr) { ; }
		~DocumentPrivate() { ; }

		const common::DocumentBase * _dataDoc;
		QScopedPointer<ACGViewer> _acgViewer;

		QMap<unsigned long, ViewFeatureBase*> _featureMap;
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
	connect(dataDoc, &common::DocumentBase::signalAppendFeature, this, &view::Document::slotAppendDataFeature);
	connect(dataDoc, &common::DocumentBase::signalRemoveFeature, this, &view::Document::slotRemoveDataFeature);
	connect(dataDoc, &common::DocumentBase::signalAfterUpdate, this, &view::Document::slotAfterDataUpdate);
}

const common::DocumentBase * Document::dataDocument() const
{
	Q_D(const Document);
	return d->_dataDoc;
}

void Document::slotAppendDataFeature(const common::DocumentBase* caller, const common::FeatureBase* obj)
{
	Q_D(Document);
	Q_ASSERT(d->_dataDoc == caller);

	const data::FeatureBase* dataFeat = dynamicCast<data::FeatureBase>(obj);
	Q_ASSERT(dataFeat != nullptr);

	ViewFeatureBase * viewFeat = dynamicCast<ViewFeatureBase>(this->appendFeature("view::ViewPolyFeature"));
	Q_ASSERT(viewFeat != nullptr);
	viewFeat->attachDataFeature(dataFeat);

	d->_featureMap.insert(obj->id(), viewFeat);
}

void Document::slotRemoveDataFeature(const common::DocumentBase* caller, const common::FeatureBase* obj)
{
	Q_D(Document);
	Q_ASSERT(d->_dataDoc == caller);

	auto it = d->_featureMap.find(obj->id());
	if (it == d->_featureMap.end())
	{
		return;
	}

	this->removeFeature(it.value()->id());
	d->_featureMap.erase(it);
}

void Document::slotAfterDataUpdate(const common::DocumentBase* caller)
{
	Q_D(Document);
	Q_ASSERT(d->_dataDoc == caller);

	this->update();
	d->_acgViewer->fitAll();
}

