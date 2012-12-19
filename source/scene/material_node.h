#ifndef _H_PUNK_SCENE_MATERIAL_NODE
#define _H_PUNK_SCENE_MATERIAL_NODE

#include "node.h"
#include "../virtual/data/material.h"

namespace Scene
{
	class PUNK_ENGINE MaterialNode : public Node
	{
	public:

		MaterialNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<MaterialNode> CreateFromFile(const System::string& path);
		static System::Proxy<MaterialNode> CreateFromStream(std::istream& stream);

		void SetMaterial(System::Proxy<Virtual::Material> value) { m_material = value; }
		System::Proxy<Virtual::Material> GetMaterial() { return m_material; }

		virtual bool Apply(AbstractVisitor* visitor);

	private:
		System::Proxy<Virtual::Material> m_material;
	};
}

REGISTER_MANAGER(L"resource.material_nodes", L"*.material_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::MATERIAL_NODE, Scene, MaterialNode, return, return);

#endif	//	_H_PUNK_SCENE_MATERIAL_NODE