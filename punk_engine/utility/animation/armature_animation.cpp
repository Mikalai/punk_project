#include "armature_animation.h"
#include "../model/armature.h"

namespace Utility
{
	ArmatureAnimation::ArmatureAnimation(Armature& armature) 
		: m_armature(armature)
	{}

	void ArmatureAnimation::UpdateBones(int frame)
	{
		for (int i = 0; i < m_armature.GetBonesCount(); ++i)
		{
			Bone* b = m_armature.GetBoneByIndex(i);
			b->UpdatePose(frame);
		}
	}

	void ArmatureAnimation::EnableTrack(const System::string& track_name, bool flag)
	{
		for (int i = 0; i < m_armature.GetBonesCount(); ++i)
		{
			m_armature.GetBoneByIndex(i)->GetAnimationMixer().EnableTrack(track_name, flag);
		}
	}

	void ArmatureAnimation::SetTrackWeight(const System::string& track_name, float value)
	{
		for (int i = 0; i < m_armature.GetBonesCount(); ++i)
		{
			m_armature.GetBoneByIndex(i)->GetAnimationMixer().SetTrackWeight(track_name, value);
		}
	}

	void ArmatureAnimation::SetLooping(const System::string& track_name, bool flag)
	{
		for (int i = 0; i < m_armature.GetBonesCount(); ++i)
		{
			m_armature.GetBoneByIndex(i)->GetAnimationMixer().SetLooping(track_name, flag);
		}
	}

}