#ifndef _H_PUNK_SCENE_MATERIAL_NODE
#define _H_PUNK_SCENE_MATERIAL_NODE

#include "node.h"
#include "../virtual/data/material.h"

namespace Scene
{
	class PUNK_ENGINE_API MaterialNode : public Node
	{
	public:

		MaterialNode();
        virtual ~MaterialNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static MaterialNode* CreateFromFile(const System::string& path);
		static MaterialNode* CreateFromStream(std::istream& stream);

		void SetMaterial(Virtual::Material* value) { m_material = value; }
		Virtual::Material* GetMaterial() { return m_material; }

		virtual bool Apply(AbstractVisitor* visitor);

        Node* Clone() const;
	private:
		//	this pointer should not be deleted in destructor
		Virtual::Material* m_material;
	};
}

#endif	//	_H_PUNK_SCENE_MATERIAL_NODE
