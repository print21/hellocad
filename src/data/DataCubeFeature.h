/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include "DataFeatureBase.h"

namespace data
{
	class CubeFeature :public FeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(data::CubeFeature);
	public:
		CubeFeature();
		~CubeFeature();

		virtual core::PolyMesh* polyMesh() const override;

	protected:
		virtual bool excute() override;

	protected:
		std::unique_ptr<core::PolyMesh> _cubeMesh;
	};
}
