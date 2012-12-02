#include "../../punk_engine.h"

bool Test()
{
	System::Proxy<Scene::SceneGraph> scene = System::Factory::Instance()->CreateFromTextFile(System::Environment::Instance()->GetModelFolder() + L"portal_test2.pmd");

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