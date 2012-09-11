#include "../../punk_engine.h"

int main()
{
	System::Window::Instance()->SetTitle(L"OpenGL Init test");
	System::Mouse::Instance()->LockInWindow(false);

	OpenGL::Driver::Instance()->Start();

	System::Window::Instance()->Loop();

	return 0;
}