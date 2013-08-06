#include "armature_node.h"
#include "../virtual/skinning/armature.h"
#include "../virtual/animation/module.h"
#include "../virtual/skinning/module.h"
#include "../utility/module.h"
#include "../system/environment.h"

namespace Scene
{
    ArmatureNode::ArmatureNode()
        : m_mixer(nullptr)
    {
    }

    ArmatureNode::~ArmatureNode()
    {
        delete m_mixer;
    }

    Virtual::ArmatureAnimationMixer* ArmatureNode::GetArmatureAnimationMixer()
    {
        if (m_mixer)
            return m_mixer;

        Virtual::Armature* armature = Cast<Virtual::Armature*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + GetStorageName()));
        if (!armature)
            return nullptr;

        m_mixer = new Virtual::ArmatureAnimationMixer(*armature);
        return m_mixer;
    }

    bool ArmatureNode::Apply(AbstractVisitor* visitor)
    {
        return visitor->Visit(this);
    }

    Node* ArmatureNode::Clone() const
    {
        ArmatureNode* node = new ArmatureNode;

        if (m_mixer)
            node->m_mixer = new Virtual::ArmatureAnimationMixer(m_mixer->GetArmature());
        else
            node->m_mixer = nullptr;

        CloneInternals(node);
        return node;
    }
}
