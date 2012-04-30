#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

namespace Utility
{
	class Animation
	{
	public:
		enum AnimationType { ANIMATION_LOOP, ANIMATION_ONCE, ANIMATION_FLIP };
	public:
		bool IsPlaying() const;
		void SetTimeWindow(float start, float end);
		void SetAnimationLaw
	private:
		AnimationType m_type;
		float m_start;
		float m_end;
	};
}

#endif