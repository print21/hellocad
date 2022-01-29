/*
 *HelloCAD a simple cad platform
 */

#include "DataPolyMesh.h"

namespace data
{
	class PolyMeshPrivate
	{
	public:
		PolyMeshPrivate() { ; }
		~PolyMeshPrivate() { ; }

		//! points container
		std::vector<PolyMesh::Pnt> _points;

		//! vertex point id container
		std::vector<PolyMesh::Index> _vertexIds;

		//! vertex color container
		std::vector<PolyMesh::Color> _vertexColors;

		//! edge point index value
		std::vector<PolyMesh::Index> _edgeIdValue;

		//! edge point color
		std::vector<PolyMesh::Color> _edgeColors;

		//! edge index range in edgeIdValue(size = edge count + 1)
		std::vector<PolyMesh::Index> _edgeIdStart;

		//! face point index value
		std::vector<PolyMesh::Index> _faceIdValue;

		//! face point color
		std::vector<PolyMesh::Color> _faceColors;

		//! face point normal
		std::vector<PolyMesh::Vec> _faceNormals;

		//! face index range in edgeIdValue(size = edge count + 1)
		std::vector<PolyMesh::Index> _faceIdStart;
	};
}

//////////////////////////////////////////////////////////////////////////
using namespace data;

PolyMesh::PolyMesh()
	:_private(new PolyMeshPrivate())
{

}

PolyMesh::~PolyMesh()
{

}

PolyMesh::Index PolyMesh::pointsCount() const
{
	return static_cast<Index>(_private->_points.size());
}

const PolyMesh::Pnt & PolyMesh::point(Index id) const
{
	assert(id >= 0 && id < _private->_points.size());
	return _private->_points[id];
}

PolyMesh::Index PolyMesh::vertexCount() const
{
	return static_cast<Index>(_private->_vertexIds.size());
}

PolyMesh::Index PolyMesh::vertexPointId(Index id) const
{
	assert(id >= 0 && id < _private->_vertexIds.size());
	return _private->_vertexIds[id];
}

PolyMesh::Color PolyMesh::vertexColor(Index id) const
{
	assert(id >= 0 && id < _private->_vertexColors.size());
	return _private->_vertexColors[id];
}

PolyMesh::Index PolyMesh::edgeCount() const
{
	if (_private->_edgeIdStart.size() < 1)
	{
		return 0;
	}

	return static_cast<PolyMesh::Index>(_private->_edgeIdStart.size()) - 1;
}

std::vector<PolyMesh::Index> PolyMesh::edgePointIds(Index id) const
{
	PolyMesh::Index cnt = edgeCount();
	if (cnt == 0)
	{
		return {};
	}

	assert(id >= 0 && id < cnt);
	PolyMesh::Index firstId = _private->_edgeIdStart[id];
	PolyMesh::Index secondId = _private->_edgeIdStart[id + 1];

	std::vector<PolyMesh::Index> index;
	if (firstId < secondId)
	{
		index.reserve(secondId - firstId);
		for (PolyMesh::Index i = firstId; i < secondId; ++i)
		{
			index.push_back(_private->_edgeIdValue[firstId + i]);
		}
	}

	return std::move(index);
}

PolyMesh::Color PolyMesh::edgeColor(Index id) const
{
	assert(id >= 0 && id < edgeCount());
	return _private->_edgeColors[id];
}

PolyMesh::Index PolyMesh::faceCount() const
{
	if (_private->_faceIdStart.size() < 1)
	{
		return 0;
	}

	return static_cast<PolyMesh::Index>(_private->_faceIdStart.size()) - 1;
}

std::vector<PolyMesh::Index> PolyMesh::facePointIds(Index id) const
{
	PolyMesh::Index cnt = faceCount();
	if (cnt == 0)
	{
		return {};
	}

	assert(id >= 0 && id < cnt);
	PolyMesh::Index firstId = _private->_faceIdStart[id];
	PolyMesh::Index secondId = _private->_faceIdStart[id + 1];

	std::vector<PolyMesh::Index> index;
	if (firstId < secondId)
	{
		index.reserve(secondId - firstId);
		for (PolyMesh::Index i = firstId; i < secondId; ++i)
		{
			index.push_back(_private->_faceIdValue[firstId + i]);
		}
	}

	return std::move(index);
}

std::vector<PolyMesh::Vec> PolyMesh::facePointNormal(Index id) const
{
	auto facePtIds = edgePointIds(id);
	std::vector<PolyMesh::Vec> normals;
	normals.reserve(facePtIds.size());

	for (auto ptId : facePtIds)
	{
		normals.emplace_back(_private->_faceNormals[ptId]);
	}

	return std::move(normals);
}

PolyMesh::Color PolyMesh::faceColor(Index id) const
{
	assert(id >= 0 && id < faceCount());
	return _private->_faceColors[id];
}

