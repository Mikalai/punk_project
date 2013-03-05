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
		};

		struct Light
		{
			enum Type { DIRECTION, OMNI, SPOT };
			Type m_type;

			Math::vec3 m_position;
			Math::vec3 m_direction;
			Math::vec3 m_color;
			float m_angle;

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
	
		SceneImpl()
		{}

		void Add(const Object& o)
		{
			m_children.push_back(o);
		}

		const Math::vec3 CalclLightOmni(const Light& light, const Math::vec3& point, const Math::vec3& normal, const Math::vec3& diffuse)
		{
			auto light_dir = (light.m_position - point).Normalized();			

			float s = normal.Dot(light_dir);

			Math::vec3 spec(1,1,1);
			auto h = (light_dir + Math::vec3(0,0,1)).Normalized();			
			auto spec_s = pow(Math::Max(normal.Dot(h), 0.0f), 2);

			if (s > 0)
				return s*diffuse.ComponentMult(light.m_color) + spec_s*spec;				
			else
				return Math::vec3(0,0,0);
		}

		const Math::vec3 CalclLightSpot(const Light& light, const Math::vec3& point, const Math::vec3& normal, const Math::vec3& diffuse)
		{
			auto light_dir = (light.m_position - point).Normalized();

			Math::vec3 spec(1,1,1);
			auto h = (light_dir + Math::vec3(0,0,1)).Normalized();			
			auto spec_s = pow(Math::Max(normal.Dot(h), 0.0f), 128);

			auto s1 = pow(Math::Max(light_dir.Dot(light.m_direction.Negated()), 0.0f), 10);
			auto s2 = normal.Dot(light_dir);
			return s1*s2*light.m_color*diffuse + spec_s*spec;
		}

		const Math::vec3 CalclLightDir(const Light& light, const Math::vec3& point, const Math::vec3& normal, const Math::vec3& diffuse)
		{
			auto light_dir = light.m_direction.Negated();
			float s = normal.Dot(light_dir);

			Math::vec3 spec(1,1,1);
			auto h = (light_dir + Math::vec3(0,0,1)).Normalized();			
			auto spec_s = pow(Math::Max(normal.Dot(h), 0.0f), 128);

			if (s > 0)
				return s*diffuse.ComponentMult(light.m_color) + spec_s*spec;

			return Math::vec3(0,0,0);
		}

		const Point Intersect(const Math::Line3D& line)
		{
			float min_t1 = 1e10;
			const Object* near_object = nullptr;
			Math::vec3 color;
			for each (auto& object in m_children)
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

			if (!near_object || min_t1 <override)
				return Point(0,0,0);

			for each(const auto& light in m_lights)
			{
				const auto p1 = line.PointAt(min_t1);
				const auto normal = (p1 - near_object->m_sphere.GetCenter()).Normalized();

				switch (light.m_type)
				{
				case Light::Type::OMNI:
					color += CalclLightOmni(light, p1, normal, near_object->m_diffuse.XYZ());
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