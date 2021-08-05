/*
* HelloCAD a simple cad platform
*/

#pragma once

namespace ACG
{
	namespace SceneGraph
	{
		class SeparatorNode;
		class CoordsysNode;
		class MaterialNode;
	}
}

namespace view
{
	class SceneCoordSys
	{
	public:
		SceneCoordSys();
		~SceneCoordSys();

		virtual void addToScene(ACG::SceneGraph::SeparatorNode * root);

	protected:
		ACG::SceneGraph::SeparatorNode* _rootNode;

		/// Node for coordinate system Material
		ACG::SceneGraph::MaterialNode* _coordsysMaterial;

		/// Node for the coordinate system
		ACG::SceneGraph::CoordsysNode* _coordsysNode;
	};
}

