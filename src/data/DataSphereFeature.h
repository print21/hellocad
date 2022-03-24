/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include "DataFeatureBase.h"

namespace data
{
	class SphereFeature :public FeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(data::SphereFeature);
	public:
		SphereFeature();
		~SphereFeature();

		virtual core::PolyMesh* triangleMesh() const override;

	protected:
		virtual bool excute() override;

	protected:
		std::unique_ptr<core::PolyMesh> _triMesh;
	};
}
