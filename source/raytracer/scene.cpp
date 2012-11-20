#include "scene_impl2.h"
#include "../math/random.h"

namespace Raytracer
{
	Scene::Scene() 
		: impl(new SceneImpl)
	{}

	Scene::Scene(const Scene& scene)
		: impl(new SceneImpl(*scene.impl))
	{
	}

	Scene::~Scene()
	{
		impl.reset(0);
	}

	const Point Scene::Intersect(const Math::Line3D& line) const
	{
		return impl->Intersect(line);
	}

	Scene Scene::CreateRandomScene(int count)
	{
		Scene res;
		//{
		//	Math::Sphere s(Math::vec3(-1.5,0,-5), 2);
		//	res.impl->Add(s);
		//}

		//{
		//	Math::Sphere s(Math::vec3(1.5,0,-5), 2);
		//	res.impl->Add(s);
		//}

		//{
		//	Math::Sphere s(Math::vec3(0,0,-5), 2);
		//	res.impl->Add(s);
		//}

		//{
		//	Math::Sphere s(Math::vec3(0,1.5,-5), 2);
		//	res.impl->Add(s);
		//}

		Math::Random rnd;
		for (int i = 0; i < count; ++i)
		{
			SceneImpl::Object o;
			o.m_sphere = Math::Sphere(Math::vec3(rnd.Uniform(-5.0f, 5.0f), rnd.Uniform(-5.0f, 5.0f), rnd.Uniform(-10.0f, -5.0f)), rnd.Uniform(1.0f, 3.0f));
			o.m_diffuse.Set(rnd.Uniform(), rnd.Uniform(), rnd.Uniform(), 1);
			if (o.m_diffuse.Length() < 0.5f)
			{
				o.m_diffuse = Math::vec4(1,1,1,1) - o.m_diffuse;
				o.m_diffuse[3] = 1.0f;
			}
			o.m_diffuse_factor = rnd.Uniform(0.5f, 0.8f);
			o.m_fresnel_factor = rnd.Uniform(0.01f, 0.15f);
			res.impl->Add(o);
		}

		auto light = SceneImpl::Light();
		light.m_type = SceneImpl::Light::OMNI;		
		res.impl->m_lights.push_back(light);

		return res;
	}
}
