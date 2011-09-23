#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include "config.h"
#include "../math/frustum.h"
#include "../system/timer.h"

namespace System
{
	class Event;
}

namespace Utility
{
	class LIB_UTILITY Camera : public Math::Frustum
	{
	protected:
		System::Timer m_timer;
		float m_mouse_sense;
		float m_phi;
		float m_psy;

		long m_move_forward;
		long m_move_backward;
		long m_move_left;
		long m_move_right;

		void OnMouseMove(System::Event* event);
		void OnIdle(System::Event* event);
	public:
		Camera();
		~Camera();
	};
}

#endif