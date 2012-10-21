#include "../../punk_engine.h"

void Test()
{
	std::unique_ptr<Utility::WorldDesc> world(new Utility::WorldDesc);

	if (!Utility::Parser::LoadWorld(System::Environment::Instance()->GetModelFolder() + L"untitled.pmd", *world))
	{
		out_error() << "Unable to create world from file" << std::endl;
		return;
	}

	System::string s = world->ToString();
	std::wcout << s.Data() << std::endl;
}

int main()
{
	Test();
	return 0;
}