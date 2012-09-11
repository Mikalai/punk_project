#ifndef PUNK_GUI_CONTROL_H
#define PUNK_GUI_CONTROL_H

#include "config.h"
#include <memory>

namespace GUI
{
	class Widget;

	class LIB_GUI UserInterface
	{
		std::auto_ptr<UserInterface> m_instance;

		struct UserInterfaceImpl;
		std::auto_ptr<UserInterfaceImpl> impl_ui;

			
		UserInterface();
		UserInterface(const UserInterface& ui);
		UserInterface& operator = (const UserInterface& ui);
	
	public:
				
		System::Descriptor CreateLayer();
		void SetActiveLayer(System::Descriptor desc);
		void AddElement(System::Descriptor parent, System::Descriptor element);
		~UserInterface();

		static UserInterface* Instance();
		static void Destroy();
	};
}

#endif