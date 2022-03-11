/*
 *HelloCAD a simple cad platform
 */

#include "AttributeView.h"

#include <QHeaderView>

namespace hellocad
{
	class AttributeViewPrivate
	{
	public:
		AttributeViewPrivate(){;}
		~AttributeViewPrivate(){;}
	};
}

using namespace hellocad;

AttributeView::AttributeView(QWidget* parent /* = nullptr */)
	:QTreeWidget(parent), d_ptr(new AttributeViewPrivate())
{
	this->header()->setStretchLastSection(true);

	QStringList headerLabel;
	headerLabel << tr("Name") << "Value";
	this->setHeaderLabels(headerLabel);

	this->header()->setSectionResizeMode(QHeaderView::Stretch);
	this->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

AttributeView::~AttributeView()
{

}

