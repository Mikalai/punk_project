#ifndef _H_PUNK_CHARACTER_RENDER
#define _H_PUNK_CHARACTER_RENDER

#include <memory>
#include "../config.h"

namespace Utility
{
	class Object;
	class Armature;
	class Camera;
}

namespace Math
{
	template<class T> class Matrix4x4;
}

namespace Render
{
	class PUNK_ENGINE CharacterRender
	{
	public:

		struct PUNK_ENGINE Parameters
		{
			Utility::Object* m_object;
			Utility::Camera* m_camera;
			Utility::Armature* m_armature;
			Math::Matrix4x4<float>* m_location;

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
		
			Parameters(Utility::Object* object, 
				Utility::Camera* camera, 
				Utility::Armature* armature,
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
		CharacterRender();
		virtual ~CharacterRender();

		virtual void Render(const Parameters* parameters);

	private:

		struct CharacterRenderImpl;
		std::auto_ptr<CharacterRenderImpl> impl;
	};
}

#endif	//	_H_PUNK_CHARACTER_RENDER