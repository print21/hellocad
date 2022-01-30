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

		//! edge point index value
		std::vector<PolyMesh::Index> _edgeIdValue;

		//! edge index range in edgeIdValue(size = edge count + 1)
		std::vector<PolyMesh::Index> _edgeIdStart;

		//! face point index value
		std::vector<PolyMesh::Index> _faceIdValue;

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

//////////////////////////////////////////////////////////////////////////

PolyMesh::Index PolyMesh::vertexCount() const
{
	return static_cast<Index>(_private->_vertexIds.size());
}

PolyMesh::Index PolyMesh::vertexPointId(Index id) const
{
	assert(id >= 0 && id < _private->_vertexIds.size());
	return _private->_vertexIds[id];
}

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

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
	std::vector<PolyMesh::Vec> normals;

	if (!_private->_faceNormals.empty())
	{
		auto facePtIds = facePointIds(id);
		normals.reserve(facePtIds.size());

		for (auto ptId : facePtIds)
		{
			normals.emplace_back(_private->_faceNormals[ptId]);
		}
	}

	return std::move(normals);
}

//////////////////////////////////////////////////////////////////////////
void PolyMesh::setPolyMesh(const std::vector<Pnt>& points, const std::vector<Index>& vertex, const std::vector<Index>& edges, const std::vector<Index>& polys)
{
	// points
	_private->_points.clear();
	_private->_points.reserve(points.size());
	_private->_points.insert(_private->_points.end(), points.end(), points.end());

	// vertex
	_private->_vertexIds.clear();
	_private->_vertexIds.reserve(vertex.size());
	_private->_vertexIds.insert(_private->_vertexIds.end(), vertex.begin(), vertex.end());

	// edge
	_private->_edgeIdStart.clear();
	_private->_edgeIdValue.clear();
	_private->_edgeIdValue.reserve(edges.size());
	_private->_edgeIdStart.push_back(static_cast<int>(_private->_edgeIdValue.size()));
	for (size_t e = 0; e < edges.size(); ++e)
	{
		if (edges[e] < 0)
		{
			_private->_edgeIdStart.push_back(static_cast<int>(_private->_edgeIdValue.size()));
		}
		else
		{
			_private->_edgeIdValue.push_back(edges[e]);
		}
	}

	if (edges.back() >= 0)
	{
		_private->_edgeIdStart.push_back(static_cast<int>(_private->_edgeIdValue.size()));
	}

	// polys
	_private->_faceIdStart.clear();
	_private->_faceIdValue.clear();
	_private->_faceIdValue.reserve(polys.size());
	_private->_faceIdStart.push_back(static_cast<int>(_private->_faceIdValue.size()));
	for (size_t f = 0; f < polys.size(); ++f)
	{
		if (polys[f] < 0)
		{
			_private->_faceIdStart.push_back(static_cast<int>(_private->_faceIdValue.size()));
		}
		else
		{
			_private->_faceIdValue.push_back(polys[f]);
		}
	}

	if (polys.back() >= 0)
	{
		_private->_faceIdStart.push_back(static_cast<int>(_private->_faceIdValue.size()));
	}
}

