#include "../../punk_engine.h"

bool Test()
{
	System::Proxy<Scene::SceneGraph> scene = System::GetFactory()->CreateFromTextFile(System::Environment::Instance()->GetModelFolder() + L"skin_test3.pmd");

	if (!scene.IsValid())
		return (out_error() << "Unable to create world from file" << std::endl, false);

	Scene::DefaultVisitor v;
	scene->GetRootNode()->Apply(&v);
	return true;
}

int main()
{
	Test();
	std::cout << "End" << std::endl;
	return 0;
}