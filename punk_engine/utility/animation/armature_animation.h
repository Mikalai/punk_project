#ifndef _H_ARMATURE_ANIMATION
#define _H_ARMATURE_ANIMATION

#include <iosfwd>
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
		void UpdateBones(float frame);
		void DisableAllTracks();
		void EnableTrack(const System::string&, bool flag);
		void SetTrackWeight(const System::string&, float value);
		void SetLooping(const System::string&, bool flag);
		void UpdateBones(float frame, int bone_id);
	
		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};
}

#endif