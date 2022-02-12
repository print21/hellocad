/*
 *HelloCAD a simple cad platform
 */

#include "TreeView.h"
#include "TreeItems.h"

#include <QHeaderView>

#include <data/DataDocument.h>
#include <data/DataAdmin.h>

using namespace hellocad;

TreeView::TreeView(QWidget* parent)
	:QTreeWidget(parent)
{
	this->setDragEnabled(false);
	this->setAcceptDrops(false);
	this->setDropIndicatorShown(false);
	this->setRootIsDecorated(true);

	QStringList labels;
	labels << tr("Name") << tr("id");

	this->setHeaderLabels(labels);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	this->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	this->header()->setStretchLastSection(true);
	this->setHeaderHidden(false);

	connect(&(data::Admin::instance()), &data::Admin::signalNewDocument, this, &TreeView::slotNewDocument);
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

