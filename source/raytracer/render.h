#ifndef _H_PUNK_RAYTRACER_RENDER
#define _H_PUNK_RAYTRACER_RENDER

#include "../config.h"

namespace ImageModule { class Image; }

namespace Raytracer
{
	class Scene;

	class PUNK_ENGINE Render
	{
		Render(const Render&);
		Render& operator = (const Render&);
	public:
		Render(int width = 320, int height = 200);
		~Render();

		bool Run(const Scene& scene, ImageModule::Image& image);

		struct RenderImpl;
		std::unique_ptr<RenderImpl> impl;
	};
}

#endif	//	_H_PUNK_RAYTRACER_RENDER