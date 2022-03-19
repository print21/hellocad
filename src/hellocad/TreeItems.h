/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QTreeWidget>

#define DOCUMENT_ITEM 1001
#define FEATURE_ITEM 1002

namespace common
{
	class DocumentBase;
	class FeatureBase;
	class AttributeBase;
}

namespace data
{
	class Document;
	class FeatureBase;
}

namespace view
{
	class ViewFeatureBase;
}

namespace hellocad
{
	class FeatureItem;
	class DocumentItem;
	class DocumentItemObject : public QObject
	{
		Q_OBJECT;
	public:
		~DocumentItemObject();

	protected:
		friend class DocumentItem;
		DocumentItemObject(data::Document* doc, DocumentItem * item, QObject* parent = nullptr);

	protected Q_SLOTS:
		void slotAppendFeature(const common::DocumentBase* caller, const common::FeatureBase* obj);
		void slotRemoveFeature(const common::DocumentBase* caller, const common::FeatureBase* obj);

	protected:
		DocumentItem* _item;
		data::Document* _doc;

		QMap<int, FeatureItem*> _childItems;
	};

	class DocumentItem : public QTreeWidgetItem
	{
	public:
		DocumentItem(data::Document* doc, QTreeWidget* view);
		DocumentItem(data::Document* doc, QTreeWidgetItem* item);
		~DocumentItem();

		const data::Document* document() const;

	protected:
		QScopedPointer<DocumentItemObject> _object;
	};

	//////////////////////////////////////////////////////////////////////////
	class FeatureItemObject : public QObject
	{
		Q_OBJECT;
	public:
		~FeatureItemObject();

	protected:
		friend class FeatureItem;
		FeatureItemObject(data::FeatureBase * feat, FeatureItem * item, QObject* parent = nullptr);

	protected Q_SLOTS:
		void slotViewAttributeChanged(const common::FeatureBase * feat, const common::AttributeBase * attr);

	protected:
		FeatureItem* _item;
		data::FeatureBase* _dataFeature;
		view::ViewFeatureBase* _viewFeature;
	};

	class FeatureItem : public QTreeWidgetItem
	{
	public:
		FeatureItem(data::FeatureBase * feat, QTreeWidgetItem* item);
		~FeatureItem();

		const data::FeatureBase* dataFeature() const;

		const view::ViewFeatureBase* viewFeature() const;

	protected:
		QScopedPointer<FeatureItemObject> _object;
	};

}
