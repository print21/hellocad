/*
 *HelloCAD a simple cad platform
 */

#include "DataCubeFeature.h"
#include "DataPolyMesh.h"

#include <core/VectorT.h>

#include <common/AttributeReal.h>

using namespace data;

CLASS_SOURCE(data::CubeFeature);

CubeFeature::CubeFeature()
{
	this->insertAttribute("Length", "common::AttributeReal", 10.0);
	this->insertAttribute("Width", "common::AttributeReal", 10.0);
	this->insertAttribute("Height", "common::AttributeReal", 10.0);
}

CubeFeature::~CubeFeature()
{

}

core::PolyMesh* CubeFeature::polyMesh() const
{
	return _cubeMesh.get();
}

bool CubeFeature::excute()
{
	if (_cubeMesh == nullptr)
	{
		_cubeMesh = std::make_unique<data::PolyMesh>();
	}

	common::AttributeReal* lengthAttr = this->attribute<common::AttributeReal>("Length");
	common::AttributeReal* widthAttr = this->attribute<common::AttributeReal>("Width");
	common::AttributeReal* heightAttr = this->attribute<common::AttributeReal>("Height");

	double length = lengthAttr->value();
	double width = widthAttr->value();
	double height = heightAttr->value();

	std::vector<core::Vec3d> points;
	std::vector<int> edges;
	std::vector<int> faces;

	points.reserve(8);
	edges.reserve(36);
	faces.reserve(30);

	points.emplace_back(0, 0, 0);
	points.emplace_back(length, 0, 0);
	points.emplace_back(length, width, 0);
	points.emplace_back(0, width, 0);
	points.emplace_back(0, 0, height);
	points.emplace_back(length, 0, height);
	points.emplace_back(0, width, height);
	points.emplace_back(0, width, height);

	edges.emplace_back(0);
	edges.emplace_back(1);
	edges.emplace_back(-1);

	edges.emplace_back(1);
	edges.emplace_back(2);
	edges.emplace_back(-1);

	edges.emplace_back(2);
	edges.emplace_back(3);
	edges.emplace_back(-1);

	edges.emplace_back(3);
	edges.emplace_back(0);
	edges.emplace_back(-1);
	//////////////////////////////////////////////////////////////////////////
	edges.emplace_back(4);
	edges.emplace_back(5);
	edges.emplace_back(-1);

	edges.emplace_back(5);
	edges.emplace_back(6);
	edges.emplace_back(-1);

	edges.emplace_back(6);
	edges.emplace_back(7);
	edges.emplace_back(-1);

	edges.emplace_back(7);
	edges.emplace_back(4);
	edges.emplace_back(-1);
	//////////////////////////////////////////////////////////////////////////
	edges.emplace_back(0);
	edges.emplace_back(4);
	edges.emplace_back(-1);

	edges.emplace_back(1);
	edges.emplace_back(5);
	edges.emplace_back(-1);

	edges.emplace_back(2);
	edges.emplace_back(6);
	edges.emplace_back(-1);

	edges.emplace_back(3);
	edges.emplace_back(7);
	edges.emplace_back(-1);

	//////////////////////////////////////////////////////////////////////////
	faces.emplace_back(0);
	faces.emplace_back(3);
	faces.emplace_back(2);
	faces.emplace_back(1);
	faces.emplace_back(-1);

	faces.emplace_back(4);
	faces.emplace_back(5);
	faces.emplace_back(6);
	faces.emplace_back(7);
	faces.emplace_back(-1);

	faces.emplace_back(0);
	faces.emplace_back(1);
	faces.emplace_back(5);
	faces.emplace_back(4);
	faces.emplace_back(-1);

	faces.emplace_back(1);
	faces.emplace_back(2);
	faces.emplace_back(6);
	faces.emplace_back(5);
	faces.emplace_back(-1);

	faces.emplace_back(2);
	faces.emplace_back(3);
	faces.emplace_back(7);
	faces.emplace_back(6);
	faces.emplace_back(-1);

	faces.emplace_back(3);
	faces.emplace_back(0);
	faces.emplace_back(4);
	faces.emplace_back(7);
	faces.emplace_back(-1);

	static_cast<data::PolyMesh*>(_cubeMesh.get())->setPolyMesh(points, {}, edges, faces);

	return true;
}

