/*
 *HelloCAD a simple cad platform
*/

#pragma once

#include <core/PolyMesh.h>
#include <common/FeatureBase.h>

namespace data
{
	class DataFeatureBase :public common::FeatureBase
	{
		Q_OBJECT
		CLASS_HEADER(data::DataFeatureBase)
	public:
		DataFeatureBase();
		~DataFeatureBase();

		virtual core::PolyMesh * polyMesh() const = 0;
	};
}
