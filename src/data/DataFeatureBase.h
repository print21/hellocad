/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include "DataExport.h"

#include <core/PolyMesh.h>
#include <common/FeatureBase.h>

namespace data
{
	class DATA_EXPORT FeatureBase :public common::FeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(data::FeatureBase);
	public:
		FeatureBase();
		~FeatureBase();

		virtual core::PolyMesh * polyMesh() const = 0;
	};
}
