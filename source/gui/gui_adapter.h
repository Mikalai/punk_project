#ifndef _H_PUNK_GUI_ADAPTER
#define _H_PUNK_GUI_ADAPTER

#include "events/interface.h"

namespace GUI
{
	class Adapter
	{
	public:
        virtual void OnSetFocusedEvent(SetFocusedEvent* event) = 0;
        virtual void OnSetUnFocusedEvent(SetUnFocusedEvent* event) = 0;
        virtual void OnMouseEnterEvent(MouseEnterEvent* event) = 0;
        virtual void OnMouseLeaveEvent(MouseLeaveEvent* event) = 0;
	};
}

#endif	//	_H_PUNK_GUI_ADAPTER
