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

		virtual core::TriMesh* triangleMesh() const override;

	protected:
		virtual bool excute() override;

	protected:
		std::unique_ptr<core::TriMesh> _triMesh;
	};
}
