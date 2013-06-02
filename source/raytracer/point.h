#ifndef _H_PUNK_RAYTRACER_POINT
#define _H_PUNK_RAYTRACER_POINT

#include "../config.h"

namespace Raytracer
{
	// stores surface properties
	class PUNK_ENGINE_API Point
	{
	public:
		Point(float _r, float _g, float _b) 
			: r(_r), g(_g), b(_b)
		{}

		float r, g, b;
	};
}

#endif	//	_H_PUNK_RAYTRACER_POINT