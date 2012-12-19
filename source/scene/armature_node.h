#ifndef _H_PUNK_SCENE_ARMATURE_NODE
#define _H_PUNK_SCENE_ARMATURE_NODE

#include "node.h"

namespace Virtual { class Armature; }

namespace Scene
{

	class PUNK_ENGINE ArmatureNode : public Node
	{

	public:
		ArmatureNode();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~ArmatureNode();		

		static System::Proxy<ArmatureNode> CreateFromFile(const System::string& path);
		static System::Proxy<ArmatureNode> CreateFromStream(std::istream& stream);
			
		virtual bool Apply(AbstractVisitor* visitor);

		void SetArmature(System::Proxy<Virtual::Armature> value);
		System::Proxy<Virtual::Armature> GetArmature();

		void SetArmatureName(const System::string& value) { m_armature_name = value; }
		const System::string& GetArmatureName() const { return m_armature_name ; }

	private:

		System::string m_armature_name;
		System::Proxy<Virtual::Armature> m_armature;

	private:
		ArmatureNode(const ArmatureNode&);
		ArmatureNode& operator = (const ArmatureNode&);
	};
}

REGISTER_MANAGER(L"resource.armature_nodes", L"*.armature_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE_NODE, Scene, ArmatureNode, return, return);

#endif	//	_H_PUNK_SCENE_ARMATURE_NODE
