/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include "ViewFeatureBase.h"

namespace ACG
{
	namespace SceneGraph
	{
		class MaterialNode;
		class TriangleNode;
#if 0
		class MeshNodeBase;
		class ShaderNode;
#endif
	}
}

namespace view
{
	class ViewPolyFeature : public ViewFeatureBase
	{
		Q_OBJECT;
		CLASS_HEADER(view::ViewPolyFeature);
	public:
		ViewPolyFeature();
		~ViewPolyFeature();

		virtual ACG::SceneGraph::SeparatorNode* rootNode() const override;

	protected:
		virtual void attachDataFeature(const common::FeatureBase* data) override;

		virtual bool excute() override;

	protected:
		ACG::SceneGraph::SeparatorNode * _rootNode;
		ACG::SceneGraph::MaterialNode* _materialNode;
		ACG::SceneGraph::TriangleNode* _triangleNode;
#if 0
		ACG::SceneGraph::MeshNodeBase* _meshNode;
		ACG::SceneGraph::ShaderNode* _shaderNode;
#endif
	};
}

