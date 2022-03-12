/*
 *HelloCAD a simple cad platform
 */

#include "DataCubeFeature.h"

#include <core/VectorT.h>
#include <common/AttributeReal.h>

using namespace data;

CLASS_SOURCE(data::CubeFeature);

CubeFeature::CubeFeature()
	:_triMesh(nullptr)
{
	this->insertAttribute("Length", "common::AttributeReal", 10.0);
	this->insertAttribute("Width", "common::AttributeReal", 10.0);
	this->insertAttribute("Height", "common::AttributeReal", 10.0);
}

CubeFeature::~CubeFeature()
{

}

core::PolyMesh* CubeFeature::triangleMesh() const
{
	return _triMesh.get();
}

bool CubeFeature::excute()
{
	if (_triMesh == nullptr)
	{
		_triMesh = std::make_unique<core::PolyMesh>();
	}
	else
	{
		_triMesh->clear();
	}

	common::AttributeReal* lengthAttr = this->attribute<common::AttributeReal>("Length");
	common::AttributeReal* widthAttr = this->attribute<common::AttributeReal>("Width");
	common::AttributeReal* heightAttr = this->attribute<common::AttributeReal>("Height");

	double length = lengthAttr->value();
	double width = widthAttr->value();
	double height = heightAttr->value();

	std::vector<core::Vec3d> points;
	points.reserve(8);
	points.emplace_back(0, 0, 0);
	points.emplace_back(length, 0, 0);
	points.emplace_back(length, width, 0);
	points.emplace_back(0, width, 0);
	points.emplace_back(0, 0, height);
	points.emplace_back(length, 0, height);
	points.emplace_back(0, width, height);
	points.emplace_back(0, width, height);

	std::vector<core::PolyMesh::VertexHandle> vhs;
	vhs.reserve(8);
	for (const auto & v : points)
	{
		core::PolyMesh::VertexHandle vh = _triMesh->add_vertex(core::PolyMesh::Point(v.data()));
		vhs.push_back(vh);
	}

	_triMesh->add_face(vhs[0], vhs[3], vhs[2]);
	_triMesh->add_face(vhs[2], vhs[1], vhs[0]);

	_triMesh->add_face(vhs[4], vhs[5], vhs[6]);
	_triMesh->add_face(vhs[6], vhs[7], vhs[4]);

	_triMesh->add_face(vhs[0], vhs[1], vhs[5]);
	_triMesh->add_face(vhs[5], vhs[4], vhs[0]);

	_triMesh->add_face(vhs[1], vhs[2], vhs[6]);
	_triMesh->add_face(vhs[6], vhs[5], vhs[1]);

	_triMesh->add_face(vhs[2], vhs[3], vhs[7]);
	_triMesh->add_face(vhs[7], vhs[6], vhs[2]);

	_triMesh->add_face(vhs[3], vhs[0], vhs[4]);
	_triMesh->add_face(vhs[4], vhs[7], vhs[3]);

	return true;
}

