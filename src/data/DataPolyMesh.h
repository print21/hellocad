/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <core/PolyMesh.h>

#include <memory>

namespace data
{
	class PolyMeshPrivate;
	class PolyMesh : public core::PolyMesh
	{
	public:
		PolyMesh();
		~PolyMesh();

		typedef int Index;
		typedef core::VectorT<double, 3> Pnt;
		typedef core::VectorT<double, 3> Vec;
		typedef core::Color4T<float> Color;

		//! point
		//! get points in polygon mesh
		virtual Index pointsCount() const override;

		//! get point by id in polygon mesh
		virtual const Pnt & point(Index id) const override;

		//! vertex
		//! get vertices count
		virtual Index vertexCount() const override;

		//! get vertex point id by vertex id
		virtual Index vertexPointId(Index id) const override;

		//! get vertex color by vertex id
		virtual Color vertexColor(Index id) const override;

		//! edge
		//! get edges count
		virtual Index edgeCount() const override;

		//! get edge point index by edge id
		virtual std::vector<Index> edgePointIds(Index id) const override;

		//! get edge point color by edge id
		virtual Color edgeColor(Index id) const override;

		//! face
		//! get faces count
		virtual Index faceCount() const override;

		//! get face point index by face id
		virtual std::vector<Index> facePointIds(Index id) const override;

		//! get face point normal by face id
		virtual std::vector<Vec> facePointNormal(Index id) const override;

		//! get face point color by face id
		virtual Color faceColor(Index id) const override;

	private:
		std::unique_ptr<PolyMeshPrivate> _private;
	};
}


