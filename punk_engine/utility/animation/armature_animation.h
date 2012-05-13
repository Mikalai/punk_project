#ifndef _H_ARMATURE_ANIMATION
#define _H_ARMATURE_ANIMATION

#include "../config.h"

namespace System { class string; }

namespace Utility
{
	class Armature;

	class LIB_UTILITY ArmatureAnimation
	{
		Armature& m_armature;
	public:
		ArmatureAnimation(Armature& armature);
		void UpdateBones(int frame);
		void EnableTrack(const System::string&, bool flag);
		void SetTrackWeight(const System::string&, float value);
		void SetLooping(const System::string&, bool flag);
	};
}

#endif