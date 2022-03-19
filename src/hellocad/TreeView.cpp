/*
 *HelloCAD a simple cad platform
 */

#include "TreeView.h"
#include "TreeItems.h"
#include "MainWindow.h"
#include "AttributeView.h"

#include <QHeaderView>

#include <data/DataDocument.h>
#include <data/DataAdmin.h>
#include <data/DataFeatureBase.h>

#include <view/ViewDocument.h>
#include <view/ViewFeatureBase.h>
#include <view/ACGViewer.h>

using namespace hellocad;

TreeView::TreeView(QWidget* parent)
	:QTreeWidget(parent)
{
	this->setDragEnabled(false);
	this->setAcceptDrops(false);
	this->setDropIndicatorShown(false);
	this->setRootIsDecorated(true);

	QStringList labels;
	labels << tr("Name") << tr("id") << tr("Visibility");

	this->setHeaderLabels(labels);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	this->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	this->header()->setStretchLastSection(true);
	this->setHeaderHidden(false);

	connect(this, &QTreeWidget::itemSelectionChanged, this, &TreeView::slotItemSelectChanged);
	connect(&(data::Admin::instance()), &data::Admin::signalNewDocument, this, &TreeView::slotNewDocument);
	connect(this, &QTreeWidget::itemChanged, this, &TreeView::slotItemValueChanged);
}

TreeView::~TreeView()
{

}

void TreeView::slotNewDocument(const common::DocumentBase* doc)
{
	const data::Document* dataDoc = dynamicCast<data::Document>(doc);
	if (dataDoc == nullptr)
	{
		return;
	}

	DocumentItem* docItem = new DocumentItem(const_cast<data::Document*>(dataDoc), this);
	this->addTopLevelItem(docItem);
	this->expandItem(docItem);
}

void TreeView::slotItemSelectChanged()
{
	QList<QTreeWidgetItem*> selItems = this->selectedItems();
	QList<DocumentItem*> docItems;
	QList<FeatureItem*> featItems;

	for (int i = 0; i < selItems.size(); ++i)
	{
		QTreeWidgetItem* item = selItems.at(i);
		if (item->type() == DOCUMENT_ITEM)
		{
			docItems.append(static_cast<DocumentItem*>(item));
		}
		else if (item->type() == FEATURE_ITEM)
		{
			featItems.append(static_cast<FeatureItem*>(item));
		}
	}

	if (!docItems.empty())
	{
		//todo;
		return;
	}

	if (!featItems.empty())
	{
		MainWindow::mainWindow()->attributeView()->setFeature(featItems.front()->dataFeature());
	}
	else
	{
		MainWindow::mainWindow()->attributeView()->setFeature(nullptr);
	}
}

void TreeView::slotItemValueChanged(QTreeWidgetItem* item, int column)
{
	if (item->type() != FEATURE_ITEM)
	{
		return;
	}

	if (column != 2)
	{
		return;
	}

	FeatureItem* featItem = static_cast<FeatureItem*>(item);
	const view::ViewFeatureBase* viewFeat = featItem->viewFeature();
	if (item->checkState(column) == Qt::Checked)
	{
		const_cast<view::ViewFeatureBase*>(viewFeat)->show();

	}
	else if (item->checkState(column) == Qt::Unchecked)
	{
		const_cast<view::ViewFeatureBase*>(viewFeat)->hide();
	}

	view::Document * viewDoc = dynamicCast<view::Document>(viewFeat->document());
	viewDoc->acgViewer()->updateViewer();
}

