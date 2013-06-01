#ifndef _H_PUNK_VIRTUAL_BONE_ANIMATION
#define _H_PUNK_VIRTUAL_BONE_ANIMATION

#include "animation.h"

namespace Virtual
{
	class BoneAnimation : public Animation
	{
		System::string m_bone_name;
	public:
		BoneAnimation();
		void SetBoneName(const System::string& value) { m_bone_name = value; }
		const System::string& GetBoneName() const { return m_bone_name; }
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~BoneAnimation();
	};
}

#endif	//	_H_PUNK_VIRTUAL_BONE_ANIMATION