#include "../../punk_engine.h"

void f(System::Event* e)
{
	std::cout << "Do nothing" << std::endl;
}

int main()
{
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(f));

	System::Window::Instance()->SetTitle(L"Event test");
	System::Mouse::Instance()->LockInWindow(false);
	System::Window::Instance()->Loop();
	return 0;
}