/*
 *HelloCAD a simple cad platform
 */

#include "ViewPolyFeature.h"
#include "ViewDocument.h"
#include "ACGViewer.h"

#include <common/AttributeBoolean.h>

#include <core/VectorT.h>
#include <data/DataFeatureBase.h>
#include <acg/Math/VectorT.hh>
#include <acg/Scenegraph/SeparatorNode.hh>
#include <acg/Scenegraph/TriangleNode.hh>
#include <acg/Scenegraph/ShaderNode.hh>
#include <acg/Scenegraph/EnvMapNode.hh>
#include <acg/Scenegraph/MeshNode2T.hh>

#include <QRandomGenerator>

namespace view
{
	typedef ACG::SceneGraph::MeshNodeT<core::PolyMesh> TriMeshNode;
}

using namespace view;

CLASS_SOURCE(view::ViewPolyFeature);

ViewPolyFeature::ViewPolyFeature()
	:_rootNode(nullptr), _materialNode(nullptr),
#if 0
	_triangleNode(nullptr)
#else
	_meshNode(nullptr)
#endif
{
}

ViewPolyFeature::~ViewPolyFeature()
{
	if (_rootNode != nullptr)
	{
		delete _rootNode;
	}

	if (_materialNode != nullptr)
	{
		delete _materialNode;
	}

#if 0
	if (_triangleNode != nullptr)
	{
		delete _triangleNode;
	}
#else
	if (_meshNode != nullptr)
	{
		delete _meshNode;
	}
#endif
}

void ViewPolyFeature::afterChange(const common::AttributeBase* prop)
{
	common::AttributeBoolean * visAttr = this->attribute<common::AttributeBoolean>("Visibility");
	if (prop == visAttr)
	{
		if (visAttr->value())
		{
			this->_rootNode->set_status(ACG::SceneGraph::BaseNode::Active);
		}
		else
		{
			this->_rootNode->set_status(ACG::SceneGraph::BaseNode::HideSubtree);
		}
	}

	ViewFeatureBase::afterChange(prop);
}

void ViewPolyFeature::attachDataFeature(const common::FeatureBase* data)
{
	ViewFeatureBase::attachDataFeature(data);

	if (_rootNode == nullptr)
	{
		_rootNode = new ACG::SceneGraph::SeparatorNode(nullptr, std::to_string(data->id()));
		std::string nodeName = std::to_string(data->id());

		int red = QRandomGenerator::global()->bounded(255);
		int green = QRandomGenerator::global()->bounded(255);
		int blue = QRandomGenerator::global()->bounded(255);

		_materialNode = new ACG::SceneGraph::MaterialNode(_rootNode, (nodeName + "::Material").c_str());
		_materialNode->set_color(ACG::Vec4f(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f));

		_textureNode = new ACG::SceneGraph::EnvMapNode(_materialNode, (nodeName + "::Texture").c_str(), true, GL_LINEAR_MIPMAP_LINEAR);
		_textureNode->drawMode(ACG::SceneGraph::DrawModes::SOLID_ENV_MAPPED);
#if 0

		_triangleNode = new ACG::SceneGraph::TriangleNode(_materialNode, (nodeName + "Triangles").c_str());
		_triangleNode->drawMode(ACG::SceneGraph::DrawModes::SOLID_FLAT_SHADED);
#else
		//std::stringstream sstr;
		//sstr << data->id() << "::" << "ShaderNode";
		//_shaderNode = new ACG::SceneGraph::ShaderNode(_rootNode, sstr.str().c_str());
		//
		//QString shaderDir = OpenFlipper::Options::shaderDirStr() + OpenFlipper::Options::dirSeparator();
		//
		//std::string shaderDirectory = std::string(shaderDir.toUtf8());
		//shaderNode_->setShaderDir(shaderDirectory);
		//
		//if (!OpenFlipper::Options::coreProfile())
		//{
		//	if (QFile(shaderDir + "Phong/Vertex.glsl").exists() && QFile(shaderDir + "Phong/Fragment.glsl").exists())
		//		shaderNode_->setShader(ACG::SceneGraph::DrawModes::SOLID_PHONG_SHADED, "Phong/Vertex.glsl", "Phong/Fragment.glsl");
		//	else
		//		std::cerr << "Shader Files for Phong not found!" << std::endl;
		//}
#endif
	}
}

ACG::SceneGraph::SeparatorNode* ViewPolyFeature::rootNode() const
{
	return _rootNode;
}

bool ViewPolyFeature::excute()
{
	if (_rootNode->parent() == nullptr)
	{
		view::Document* viewDoc = dynamicCast<view::Document>(this->document());
		Q_ASSERT(viewDoc != nullptr);

		ACGViewer* viewer = viewDoc->acgViewer();
		viewer->addToViewer(_rootNode);
	}

	const data::FeatureBase* data = dynamicCast<data::FeatureBase>(this->_data);
	if (data == nullptr)
	{
		return false;
	}

	core::PolyMesh* mesh = data->triangleMesh();
#if 0
	_triangleNode->clear();
	if (mesh == nullptr)
	{
		return false;
	}

	for (auto it = mesh->faces_begin(), itend = mesh->faces_end(); it != itend; ++it)
	{
		std::vector<ACG::Vec3f> pnts;
		pnts.reserve(3);
		for (auto vit = mesh->fv_begin(it), vitend = mesh->fv_end(it); vit != vitend; ++vit)
		{
			const core::PolyMesh::Point& pt = mesh->point(vit);
			pnts.emplace_back(pt[0], pt[1], pt[2]);
		}

		_triangleNode->add_triangle(pnts[0], pnts[1], pnts[2]);
	}
#else
	unsigned long dataObjId = data->id();
	std::stringstream sstr;
	sstr << dataObjId << "::" << "MeshNode";
	if (_meshNode != nullptr)
	{
		delete _meshNode;//remove from parent in destruct.
		_meshNode = nullptr;
	}

	_meshNode = new TriMeshNode(*mesh, _textureNode, sstr.str().c_str());
	if (mesh->has_vertex_normals())
	{
		_meshNode->drawMode(ACG::SceneGraph::DrawModes::SOLID_SMOOTH_SHADED);
	}
	else if (mesh->has_face_normals())
	{
		_meshNode->drawMode(ACG::SceneGraph::DrawModes::SOLID_FLAT_SHADED);
	}
	else
	{
		std::cerr << "triangle mesh has no normals." << "\n";
	}
	static_cast<TriMeshNode*>(_meshNode)->update_geometry();
#endif
	return true;
}

