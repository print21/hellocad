/*
 *HelloCAD a simple cad platform
*/

#include "ViewFeatureBase.h"

using namespace view;

CLASS_SOURCE_ABSTRACT(view::ViewFeatureBase);

ViewFeatureBase::ViewFeatureBase()
	:_data(nullptr)
{

}

ViewFeatureBase::~ViewFeatureBase()
{

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

