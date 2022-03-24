/*
 *HelloCAD a simple cad platform
 */

#include "DataSphereFeature.h"

#include <core/VectorT.h>
#include <common/AttributeReal.h>

using namespace data;

CLASS_SOURCE(data::SphereFeature);

SphereFeature::SphereFeature()
	:_triMesh(nullptr)
{
	this->insertAttribute("Radius", "common::AttributeReal", 10.0);
}

SphereFeature::~SphereFeature()
{

}

core::PolyMesh* SphereFeature::triangleMesh() const
{
	return _triMesh.get();
}

bool SphereFeature::excute()
{
	if (_triMesh == nullptr)
	{
		_triMesh = std::make_unique<core::PolyMesh>();
		_triMesh->request_face_normals();
		_triMesh->request_vertex_normals();
	}
	else
	{
		_triMesh->clear();
	}

	common::AttributeReal* radiusAttr = this->attribute<common::AttributeReal>("Radius");

	double radius = radiusAttr->value();
	double minU = 0.0;
	double maxU = M_PI * 2.0;
	double minV = -M_PI;
	double maxV = M_PI;

	int uCnt = 50;
	int vCnt = 50;
	std::vector<core::PolyMesh::VertexHandle> vhs;
	vhs.reserve((uCnt + 1) * (vCnt + 1));
	for (int u = 0; u <= uCnt; ++u)
	{
		double uu = minU + u * (maxU - minU) / uCnt;
		for (int v = 0; v <= vCnt; ++v)
		{
			double vv = minV + v * (maxV - minV) / vCnt;

			double xx = radius * std::cos(uu) * std::cos(vv);
			double yy = radius * std::sin(uu) * std::cos(vv);
			double zz = radius * std::sin(vv);

			core::PolyMesh::VertexHandle vh = _triMesh->add_vertex(core::PolyMesh::Point(xx, yy, zz));
			vhs.push_back(vh);
		}
	}

	for (int u = 0; u < uCnt; ++u)
	{
		for (int v = 0; v < vCnt; ++v)
		{
			int id1 = u * vCnt + v;
			int id2 = u * vCnt + v + 1;
			int id3 = (u + 1) * vCnt + v + 1;
			int id4 = (u + 1) * vCnt + v;
			
			_triMesh->add_face(vhs[id1], vhs[id2], vhs[id3]);
			_triMesh->add_face(vhs[id3], vhs[id4], vhs[id1]);
		}
	}

	_triMesh->update_face_normals();
	_triMesh->update_vertex_normals();

	return true;
}

