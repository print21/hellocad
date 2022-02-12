/*
 *HelloCAD a simple cad platform
 */

#include "TreeItems.h"

#include <data/DataDocument.h>
#include <data/DataFeatureBase.h>

using namespace hellocad;

DocumentItemObject::DocumentItemObject(data::Document* doc, DocumentItem* item, QObject* parent /*= nullptr*/)
	:QObject(nullptr), _doc(doc), _item(item)
{
	common::DocumentBase * base = dynamicCast<common::DocumentBase>(_doc);
	connect(base, &common::DocumentBase::signalAppendFeature, this, &DocumentItemObject::slotAppendFeature);
	connect(base, &common::DocumentBase::signalRemoveFeature, this, &DocumentItemObject::slotRemoveFeature);
}

DocumentItemObject::~DocumentItemObject()
{

}

void DocumentItemObject::slotAppendFeature(const common::DocumentBase* caller, const common::FeatureBase* obj)
{
	Q_ASSERT(caller == _doc);
	Q_ASSERT(!_childItems.contains(obj->id()));

	const data::FeatureBase* dataFeat = dynamicCast<data::FeatureBase>(obj);
	if (dataFeat == nullptr)
	{
		return;
	}

	FeatureItem* newItem = new FeatureItem(const_cast<data::FeatureBase*>(dataFeat), _item);
	_item->addChild(newItem);

	_item->setExpanded(true);
}

void DocumentItemObject::slotRemoveFeature(const common::DocumentBase* caller, const common::FeatureBase* obj)
{
	Q_ASSERT(caller == _doc);
	auto it = _childItems.find(obj->id());
	if (it != _childItems.end())
	{
		_item->removeChild(it.value());
	}
}

//////////////////////////////////////////////////////////////////////////

DocumentItem::DocumentItem(data::Document* doc, QTreeWidget* view)
	:_object(new DocumentItemObject(doc, this)), QTreeWidgetItem(view, DOCUMENT_ITEM)
{
	this->setText(0, doc->documentName());
	this->setData(0, Qt::UserRole, doc->documentName());
}

DocumentItem::DocumentItem(data::Document* doc, QTreeWidgetItem* item)
	: _object(new DocumentItemObject(doc, this)), QTreeWidgetItem(item, DOCUMENT_ITEM)
{

}

DocumentItem::~DocumentItem()
{

}

const data::Document* DocumentItem::document() const
{
	return _object->_doc;
}

//////////////////////////////////////////////////////////////////////////

FeatureItemObject::FeatureItemObject(data::FeatureBase* feat, QObject* parent /*= nullptr*/)
	:QObject(nullptr), _feature(feat)
{

}

FeatureItemObject::~FeatureItemObject()
{

}

//////////////////////////////////////////////////////////////////////////

FeatureItem::FeatureItem(data::FeatureBase* feat, QTreeWidgetItem* item)
	:_object(new FeatureItemObject(feat)), QTreeWidgetItem(item, FEATURE_ITEM)
{
	this->setText(0, QString::number(feat->id()));
	this->setText(1, QString::number(feat->id()));
	this->setData(0, Qt::UserRole, QVariant::fromValue(feat->id()));
}

FeatureItem::~FeatureItem()
{

}

const data::FeatureBase* FeatureItem::feature() const
{
	return _object->_feature;
}
