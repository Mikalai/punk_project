#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include "../config.h"
#include "../math/frustum.h"
#include "../system/timer.h"

namespace System
{
	class Event;
}

namespace Utility
{
	class PUNK_ENGINE Camera : public Math::Frustum
	{
	protected:
		enum Type { CAMERA_TYPE_FPS, CAMERA_TYPE_TPS, CAMERA_TYPE_RTS };

		Type m_camera_type;

		System::Timer m_timer;
		float m_mouse_sense;
		float m_phi;
		float m_psy;

		long m_move_forward;
		long m_move_backward;
		long m_move_left;
		long m_move_right;

		float m_height_offset;
		float m_base_height;

	public:

		Camera();
		~Camera();		

		void SetBaseHeight(float value) { m_base_height = value; }
		float GetBaseHeight() const { return m_base_height; }
		void SetHeightOffset(float value) { m_height_offset = value; }
		float GetHeightOffset() const { return m_height_offset; }

		void OnMouseMove(System::Event* event);
		void OnIdle(System::Event* event);
		void OnKeyDown(System::Event* event);
		void OnMouseScroll(System::Event* event);
		void OnResize(System::Event* event);
	};
	
	typedef Camera* CameraRef;
}

#endif