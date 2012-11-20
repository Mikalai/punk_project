#ifndef _H_PUNK_RAYTRACER_RENDER_IMPL2
#define _H_PUNK_RAYTRACER_RENDER_IMPL2

#include "../math/frustum.h"
#include "../math/line3d.h"
#include "../math/vec3.h"
#include "../math/helper.h"

#include "../images/images.h"

#include "render.h"
#include "scene.h"
#include "point.h"

namespace Raytracer
{
	class Render::RenderImpl
	{
		int m_width;
		int m_height;
		float m_fov;
			
	public:

		RenderImpl(int width = 320, int height = 200)
			: m_width(width)
			, m_height(height)
			, m_fov(3.14/2)
		{}

		bool Run(const Scene& scene, ImageModule::Image& image)
		{			
			image.Create(m_width, m_height, 3);			
			image.SetFormat(ImageModule::IMAGE_FORMAT_RGB);
			image.SetDepth(8);

			Math::vec3 origin(0,0,0);
			float z = -1/tan(m_fov/2.0f);
			float a = (float)m_height / (float)m_width;

			for (int y = 0; y < m_height; ++y)
			{
				for (int x = 0; x < m_width; ++x)
				{					
					Math::vec3 destination(2.0f*(float)x/(float)m_width-1, 2.0f*a*(float)y/(float)m_height-a, z);

					Math::Line3D ray(origin, destination);

					const Point p = scene.Intersect(ray);

					image.SetPixelComponent(x, m_height-y-1, 0, Math::Min(255.0*p.r, 255.0));
					image.SetPixelComponent(x, m_height-y-1, 1, Math::Min(255.0*p.g, 255.0));
					image.SetPixelComponent(x, m_height-y-1, 2, Math::Min(255.0*p.b, 255.0));
				/*	image.SetPixelComponent(x, m_height-y-1, 0, 255.0*p.r);
					image.SetPixelComponent(x, m_height-y-1, 1, 255.0*p.g);
					image.SetPixelComponent(x, m_height-y-1, 2, 255.0*p.b);*/
				}
			}

			return true;
		}

	};
}

#endif	//	_H_PUNK_RAYTRACER_RENDER_IMPL1