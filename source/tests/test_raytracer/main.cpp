#include "../../punk_engine.h"

int main()
{
	Raytracer::Scene scene = Raytracer::Scene::CreateRandomScene(30);	
	Raytracer::Render render(1920, 1080);
	ImageModule::Image image;

	render.Run(scene, image);

	ImageModule::Exporter e;
	e.Export(L"test.png", image);

	return 0;
}