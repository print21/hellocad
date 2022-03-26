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
		class EnvMapNode;
		class MeshNodeBase;
		class ShaderNode;
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

		virtual void afterChange(const common::AttributeBase* prop) override;

	protected:
		ACG::SceneGraph::SeparatorNode* _rootNode;
		ACG::SceneGraph::MaterialNode* _materialNode;
		ACG::SceneGraph::EnvMapNode* _textureNode;
		ACG::SceneGraph::MeshNodeBase* _meshNode;
		ACG::SceneGraph::ShaderNode* _shaderNode;
	};
}

