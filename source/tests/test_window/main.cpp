#include "../../punk_engine.h"

int main()
{
	System::Window::Instance()->SetTitle(L"Punk window test");	
	System::Mouse::Instance()->LockInWindow(false);
	System::Window::Instance()->Loop();
	return 0;
}