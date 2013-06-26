#ifndef _H_PUNK_RAYTRACER_SCENE_IMPL1
#define _H_PUNK_RAYTRACER_SCENE_IMPL1

#include "../math/line3d.h"
#include "../math/sphere.h"
#include "../math/relations.h"
#include "../math/vec4.h"
#include "../math/helper.h"

#include "scene.h"

namespace Raytracer
{
	struct Scene::SceneImpl
	{
		struct Object
		{
			Math::Sphere m_sphere;
			Math::vec4 m_diffuse;
			float m_diffuse_factor;
			float m_fresnel_factor;

			Object() : m_diffuse_factor(0.8f) {}
		};

		struct Light
		{
			enum Type { DIRECTION, OMNI, SPOT };
            Math::vec3 m_position;
			Math::vec3 m_direction;
			Math::vec3 m_color;
			float m_angle;
            Type m_type;

			Light()
				: m_position(0,0,0)
				, m_direction(0, 0, -1)
				, m_color(1,1,1)
				, m_angle(3.14f/2.0f)
				, m_type(OMNI)
			{}
		};

		std::vector<Light> m_lights;
		std::vector<Object> m_children;
		float m_env_factor;

		SceneImpl()
			: m_env_factor(1.0f)
		{}

		void Add(const Object& o)
		{
			m_children.push_back(o);
		}

		float FresnelFactorFunction(const Math::vec3& view, const Math::vec3& light, float factor)
		{
			Math::vec3 h = (view + light).Normalized();
			const Math::vec3& l = light;
			float l_h = l.Dot(h);
			float g = sqrt(factor*factor - 1.0f + l_h * l_h);
			float g_minus_lh = g - l_h;
			float g_plus_lh = g + l_h;

			float f = 0.5f * (g_minus_lh*g_minus_lh) / (g_plus_lh*g_plus_lh);

			float a = l_h*(g_plus_lh) - 1.0f;
			float b = l_h*(g_minus_lh) + 1.0f;

			f *= (a*a/b*b + 1.0f);
			return f;
		}

		//	m is a microfacet parameter root mean of the distribution
		float IsotropicMicrofaceFunction(const Math::vec3& v, const Math::vec3& l, const Math::vec3& n, float m)
		{
			const Math::vec3 h = (l+v).Normalized();
			float nh = n.Dot(h);
			float nh2 = nh*nh;

			float d = 1.0f / (4.0f*m*m*nh2*nh2);
			d *= exp((nh2-1.0f)/(m*m*nh2));
			return d;
		}

		float GeometricalAttenuationFunction(const Math::vec3& v, const Math::vec3& l, const Math::vec3& n)
		{
			const Math::vec3 h = (l+v).Normalized();
			float nh = n.Dot(h);
			float nv = n.Dot(v);
			float lh = l.Dot(h);
			float nl = n.Dot(l);

			float a = 1.0f;
			float b = 2*nh*nv/lh;
			float c = 2*nh*nl/lh;

			float g = Math::Min(a,b,c);
			return g;
		}

		float CookTorrenceFunction(const Math::vec3& v, const Math::vec3& l, const Math::vec3& n, float factor, float m)
		{
			float f = FresnelFactorFunction(v, l, factor);
			float d = IsotropicMicrofaceFunction(v, l, n, m);
			float g = GeometricalAttenuationFunction(v, l, n);

			float r = f*d*g/n.Dot(l);
			return r;
		}

		const Math::vec3 CalclLightOmni(const Light& light, const Math::vec3& point, const Math::vec3& normal, const Math::vec3& diffuse, float k, float m)
		{
			auto light_dir = (light.m_position - point).Normalized();
			auto view_dir = Math::vec3(0,0,1);
			float s = normal.Dot(light_dir);

			Math::vec3 spec(1,1,1);
            //auto h = (light_dir + Math::vec3(0,0,1)).Normalized();
			auto spec_s = CookTorrenceFunction(view_dir, light_dir, normal, 1.333f, m);

			if (s > 0)
				return k*s*diffuse.ComponentMult(light.m_color) + (1.0f - k)*spec_s*spec;
			else
				return Math::vec3(0,0,0);
		}

		const Math::vec3 CalclLightSpot(const Light& light, const Math::vec3& point, const Math::vec3& normal, const Math::vec3& diffuse)
		{
			auto light_dir = (light.m_position - point).Normalized();

			Math::vec3 spec(1,1,1);
			Math::vec3 h = (light_dir + Math::vec3(0,0,1)).Normalized();
			float spec_s = powf(Math::Max(normal.Dot(h), 0.0f), 128);

			float s1 = powf(Math::Max(light_dir.Dot(light.m_direction.Negated()), 0.0f), 10);
			float s2 = normal.Dot(light_dir);
			return s1*s2*light.m_color*diffuse + spec_s*spec;
		}

        const Math::vec3 CalclLightDir(const Light& light, const Math::vec3& /*point*/, const Math::vec3& normal, const Math::vec3& diffuse)
		{
            auto light_dir = Math::vec3(light.m_direction.Negated());
			float s = normal.Dot(light_dir);

			Math::vec3 spec(1,1,1);
			auto h = (light_dir + Math::vec3(0,0,1)).Normalized();
			auto spec_s = powf(Math::Max(normal.Dot(h), 0.0f), 128);

			if (s > 0)
				return s*diffuse.ComponentMult(light.m_color) + spec_s*spec;

			return Math::vec3(0,0,0);
		}

		const Point Intersect(const Math::Line3D& line)
		{
			float min_t1 = 1e10;
			const Object* near_object = nullptr;
			Math::vec3 color;
			for (auto& object : m_children)
			{
				float t1, t2;
				Math::vec3 p1, p2;
				Math::Relation res = Math::CrossLineSphere(line, object.m_sphere, t1, t2);
				if (res != Math::Relation::INTERSECT_2)
					continue;

				if (min_t1 > t1)
				{
					near_object = &object;
					min_t1 = t1;
				}

				if (min_t1 > t2)
				{
					near_object = &object;
					min_t1 = t2;
				}
			}

			if (!near_object || min_t1 <= 0)
				return Point(0,0,0);

			for (const auto& light : m_lights)
			{
				const auto p1 = line.PointAt(min_t1);
				const auto normal = (p1 - near_object->m_sphere.GetCenter()).Normalized();

				switch (light.m_type)
				{
				case Light::Type::OMNI:
					color += CalclLightOmni(light, p1, normal, near_object->m_diffuse.XYZ(), near_object->m_diffuse_factor, near_object->m_fresnel_factor);
					break;
				case Light::Type::SPOT:
					color += CalclLightSpot(light, p1, normal, near_object->m_diffuse.XYZ());
					break;
				case Light::Type::DIRECTION:
					color += CalclLightDir(light, p1, normal, near_object->m_diffuse.XYZ());
					break;
				}
			}

			return Point(color.X(), color.Y(), color.Z());
		}
	};
}

#endif	//	_H_PUNK_RAYTRACER_SCENE_IMPL1
