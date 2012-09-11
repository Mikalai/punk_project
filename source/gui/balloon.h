#ifndef _H_PUNK_GUI_BALLOON
#define _H_PUNK_GUI_BALLOON

#include "widget.h"

namespace GUI
{
	class IGUIRender;

	class LIB_GUI Balloon : public Widget
	{
		System::string m_message;
		float m_show_time;
		float m_appear_time;
		float m_disappear_time;
		float m_cur_time;
		float m_scale;
	public:
		Balloon(float x = 0.1, float y = 0.1, float w = 0.3, float h = 0.1, const System::string& message = L"Hello world", Widget* p = 0);
		virtual ~Balloon();
		void Blink();
		float GetScale() const;
		void SetShowTime(float value);
		float GetShowTime() const;
		void SetAppearTime(float v);
		float GetAppearTime() const;
		void SetDisappearTime(float v);
		float GetDisappearTime() const;

		virtual void Render(IGUIRender* render) const;

	protected:
		void OnIdle(System::IdleEvent* e);
	};
}

#endif	//_H_PUNK_GUI_BALLOON