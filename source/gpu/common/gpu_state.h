#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../config.h"
#include "../../math/module.h"
#include "../../system/state_manager.h"
#include "../../system/poolable.h"
#include "../../virtual/interface.h"
#include "render_target.h"
#include "lighting/module.h"
#include "blending/module.h"
#include "fog/module.h"
#include "config.h"

namespace GPU
{
	class Texture2D;
	class AbstractRenderPolicy;

	class PUNK_ENGINE CoreState : public System::Poolable<CoreState>
	{
	public:

		CoreState();
		~CoreState();

		Math::mat4 m_world;
		Math::mat4 m_local;		
		Math::mat4 m_projection;
		Math::mat4 m_view;
		//	corresponds to the part of the world matrix of the skin mesh
		Math::mat4 m_armature_world;
		Math::mat4 m_bone_world;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_text_color;
		Math::vec4 m_no_diffuse_texture_color;
		Math::vec4 m_specular_color;
		float m_specular_factor;		
		Math::vec3 m_camera_position;
		Math::mat4 m_texture_matrix;
		Math::vec2 m_terran_position;
		Math::ClipSpace m_clip_space;
		float m_ambient_color;

		int m_terrain_level;
		int m_terrain_i;
		int m_terrain_j;
		int m_terrain_slices;

		LightModel m_light_model;
		LightAttenuation m_light_attenuation;
		float m_light_constant_attenuation;
		float m_light_linear_attenuation;
		float m_light_quadric_attenuation;
		bool m_depth_test;
		bool m_enable_blending;
		bool m_line_smooth;
		bool m_multisample;
		bool m_polygon_smooth;
		bool m_enable_wireframe;
		bool m_use_diffuse_texture;
		bool m_use_text_texture;
		bool m_enable_shadows;
		bool m_enable_lighting;
		bool m_enable_diffuse_shading;		
		bool m_enable_skinning;
		bool m_enable_terrain;
		bool m_enable_water;
		bool m_enable_texture;
		bool m_enable_font_rendering;
        bool m_enable_vertex_color;
		bool m_cast_shadows;
		bool m_receive_shadows;
		bool m_enable_text_rendering;
		float m_clear_depth;

		Math::mat4 m_bone_matrix[256];
		float m_line_width;
		float m_point_size;
		int m_diffuse_slot_0;
		int m_diffuse_slot_1;
		int m_normal_slot;
		int m_text_slot;
		int m_height_map_slot;

		BlendFunction m_blend_src;
		BlendFunction m_blend_dst;
		Math::vec4 m_blend_color;

		const Texture2D* m_diffuse_map_1;
		const Texture2D* m_diffuse_map_0;
		const Texture2D* m_normal_map;
		const Texture2D* m_height_map;
		const Texture2D* m_specular_map;
		const Texture2D* m_text_map;

        //  added on 01.05.2013        
		Texture2D* m_color_buffer;
		Texture2D* m_depth_buffer;
        Math::vec4 m_clear_color;

		//	added on 15.05.2013
		FogDescription m_fog;

		//	this pointers should not be deleted in destructor
		LightParameters m_lights[MAX_LIGHTS];
		//	this pointers should not be deleted in destructor

		CoreState* Clone();
	};	
}

#endif	//	_H_PUNK_RENDER_STATE
