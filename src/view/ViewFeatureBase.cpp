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
}

bool ViewFeatureBase::excute()
{
	return true;
}
