#include "render_impl2.h"

namespace Raytracer
{
	Render::Render(int width, int height)
		: impl(new RenderImpl(width, height))
	{}

	Render::~Render()
	{
		impl.reset(0);
	}

	bool Render::Run(const Scene& scene, ImageModule::Image& image)
	{
		return impl->Run(scene, image);
	}
}