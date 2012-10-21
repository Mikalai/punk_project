#ifndef _H_PUNK_RENDER_SOLID_OBJECT
#define _H_PUNK_RENDER_SOLID_OBJECT

#include <memory>
#include "../config.h"

namespace Utility
{
	class Entity;
	class Armature;
	class Camera;
}

namespace OpenGL
{
	class RenderPass;
}

namespace Math
{
	template<class T> class Matrix4x4;
}

namespace Render
{
	class PUNK_ENGINE SolidObjectRender
	{
	public:

		struct PUNK_ENGINE Parameters
		{
			Utility::Entity* m_object;
			Utility::Camera* m_camera;
			Math::Matrix4x4<float>* m_location;
			OpenGL::RenderPass* m_render_pass;

			bool m_render_production;	//	other flags not used
			bool m_use_diffuse_map;
			bool m_use_normal_map;
			bool m_show_only_texture_coords;
			bool m_show_only_normals;
			bool m_show_only_bitangets;
			bool m_show_only_tangents;
			bool m_show_only_diffuse_map;
			bool m_show_only_normal_map;
			
			bool m_show_bbox;
			bool m_show_aabb;
		
		public:
		
			Parameters(Utility::Entity* object, 
				Utility::Camera* camera, 
				OpenGL::RenderPass* pass,
				Math::Matrix4x4<float>* location,
				bool render_production = true, 
				bool use_diffuse_map = false, 
				bool use_normal_map = false,
				bool show_only_texture_coords = false, 
				bool show_only_normals = false,
				bool show_only_bitangents = false,
				bool show_only_tangents = false,
				bool show_only_diffuse_map = false,
				bool show_only_normal_map = false,
				bool show_bbox = false,
				bool show_aabb = false);

			friend class CharacterRender;
		};

	public:
		SolidObjectRender();
		virtual ~SolidObjectRender();

		virtual void Render(const Parameters* parameters);

	private:

		void Render(const Utility::Entity* object, const Math::Matrix4x4<float>* parent, const Parameters* parameters);
		struct SolidObjectRenderImpl;
		std::auto_ptr<SolidObjectRenderImpl> impl;
	};
}

#endif	//	_H_PUNK_CHARACTER_RENDER