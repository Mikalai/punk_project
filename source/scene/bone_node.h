/*
*	Bone node is used when transform is bind to the bone of the 
*	armature
*/
#ifndef _H_PUNK_SCENE_BONE_NODE
#define _H_PUNK_SCENE_BONE_NODE

#include "node.h"

namespace Scene
{

	class PUNK_ENGINE BoneNode : public Node
	{

	public:
		BoneNode();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~BoneNode();		

		static System::Proxy<BoneNode> CreateFromFile(const System::string& path);
		static System::Proxy<BoneNode> CreateFromStream(std::istream& stream);
			
		virtual bool Apply(AbstractVisitor* visitor);

	private:
		BoneNode(const BoneNode&);
		BoneNode& operator = (const BoneNode&);
	};
}

REGISTER_MANAGER(L"resource.bone_nodes", L"*.bone_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE_NODE, Scene, BoneNode, return, return);

#endif	//	_H_PUNK_SCENE_BONE_NODE
