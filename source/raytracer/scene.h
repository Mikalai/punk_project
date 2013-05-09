#ifndef _H_PUNK_RAYTRACER_SCENE
#define _H_PUNK_RAYTRACER_SCENE

#include <memory>
#include "../config.h"
#include "point.h"

namespace Math { class Line3D; }

namespace Raytracer
{
	class PUNK_ENGINE Scene
	{
	public:
		Scene();
		Scene(const Scene& scene);
		~Scene();

		const Point Intersect(const Math::Line3D& ray) const;
		
		static Scene CreateRandomScene(int count);

	public:
		struct SceneImpl;
		std::unique_ptr<SceneImpl> impl;
	};
}

#endif	//  _H_PUNK_RAYTRACER_SCENE
