/*
*	Bone node is used when transform is bind to the bone of the 
*	armature
*/
#ifndef _H_PUNK_SCENE_BONE_NODE
#define _H_PUNK_SCENE_BONE_NODE

#include "node.h"

namespace Virtual { class Bone; }

namespace Scene
{

	class PUNK_ENGINE_PUBLIC BoneNode : public Node
	{

	public:
		BoneNode();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~BoneNode();		

		static BoneNode* CreateFromFile(const System::string& path);
		static BoneNode* CreateFromStream(std::istream& stream);
			
		virtual bool Apply(AbstractVisitor* visitor);

		Virtual::Bone* GetBone();
		void SetBone(Virtual::Bone* value);

	private:
		BoneNode(const BoneNode&);
		BoneNode& operator = (const BoneNode&);

		Virtual::Bone* m_bone;
	};
}

#endif	//	_H_PUNK_SCENE_BONE_NODE
