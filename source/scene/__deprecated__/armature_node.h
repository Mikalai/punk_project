#ifndef _H_PUNK_SCENE_ARMATURE_NODE
#define _H_PUNK_SCENE_ARMATURE_NODE

#include "node.h"

namespace Virtual
{
    class Armature;
    class ArmatureAnimationMixer;
}

namespace Scene
{

	class PUNK_ENGINE_API ArmatureNode : public Node
	{

	public:
		ArmatureNode();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~ArmatureNode();		

		static ArmatureNode* CreateFromFile(const System::string& path);
		static ArmatureNode* CreateFromStream(std::istream& stream);
			
		virtual bool Apply(AbstractVisitor* visitor);

        Virtual::ArmatureAnimationMixer* GetArmatureAnimationMixer();
        virtual Node* Clone() const override;

	private:

        Virtual::ArmatureAnimationMixer* m_mixer;

	private:
		ArmatureNode(const ArmatureNode&);
		ArmatureNode& operator = (const ArmatureNode&);
	};
}

#endif	//	_H_PUNK_SCENE_ARMATURE_NODE
