/*
 *HelloCAD a simple cad platform
*/

#include "ViewFeatureBase.h"

#include <common/AttributeBoolean.h>

using namespace view;

CLASS_SOURCE_ABSTRACT(view::ViewFeatureBase);

ViewFeatureBase::ViewFeatureBase()
	:_data(nullptr)
{
	this->insertAttribute("Visibility", "common::AttributeBoolean", true, static_cast<unsigned short>(common::AttributeBase::TYPE::SILENT));
}

ViewFeatureBase::~ViewFeatureBase()
{

}

void ViewFeatureBase::hide()
{
	common::AttributeBoolean* visAttr = this->attribute<common::AttributeBoolean>("Visibility");
	if (visAttr->value())
	{
		visAttr->setValue(false);
	}
}

void ViewFeatureBase::show()
{
	common::AttributeBoolean* visAttr = this->attribute<common::AttributeBoolean>("Visibility");
	if (!visAttr->value())
	{
		visAttr->setValue(true);
	}
}

bool ViewFeatureBase::visible() const
{
	common::AttributeBoolean * visAttr = this->attribute<common::AttributeBoolean>("Visibility");
	return visAttr->value();
}

void ViewFeatureBase::attachDataFeature(const common::FeatureBase* data)
{
	Q_ASSERT(_data == nullptr);
	_data = data;

	connect(_data, &common::FeatureBase::signalStatusChanged, this, &ViewFeatureBase::slotDataFeatureStatusChanged);
}

bool ViewFeatureBase::excute()
{
	return true;
}

void ViewFeatureBase::slotDataFeatureStatusChanged(const common::FeatureBase* sender, STATUS st, bool value)
{
	Q_ASSERT(sender == _data);

	if (st == FeatureBase::STATUS::STATUS_DIRTY ||
		st == FeatureBase::STATUS::STATUS_ERROR)
	{
		this->setStatus(FeatureBase::STATUS::STATUS_DIRTY, true);
	}
}

