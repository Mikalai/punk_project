#include "../../punk_engine.h"

void f()
{
	Utility::WorldDesc world_desc;
	if (!Utility::Parser::LoadWorld(System::Environment::Instance()->GetModelFolder() + L"shop_interior2.pmd", world_desc))
	{
		out_error() << "Can't load world from PMD file" << std::endl;
		return;
	}

//	Scene::Node
}

int main()
{
}