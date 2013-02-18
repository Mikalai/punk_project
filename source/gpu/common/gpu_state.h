#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../config.h"
#include "../../math/module.h"
#include "../../system/state_manager.h"
#include "../../virtual/interface.h"

namespace GPU
{
	class AbstractRenderPolicy;

	class PUNK_ENGINE CoreState
	{
	public:
		enum BlendOperation { BLEND_SRC_ONE_MINUS_ALPHA };

		CoreState();
		~CoreState();

		Math::mat4 m_local;		
		Math::mat4 m_projection;
		Math::mat4 m_view;
		Math::mat4 m_mesh_matrix_local;
		//	corresponds to the part of the world matrix of the skin mesh
		Math::mat4 m_armature_world;
		Math::mat4 m_bone_world;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_text_color;
		Math::vec4 m_no_diffuse_texture_color;
		Math::vec4 m_specular_color;
		Math::vec4 m_specular_factor;		
		Math::vec3 m_camera_position;
		Math::mat2 m_texture_matrix;
		Math::vec2 m_terran_position;
		Math::ClipSpace m_clip_space;

		int m_terrain_level;
		int m_terrain_i;
		int m_terrain_j;
		int m_terrain_slices;

		BlendOperation m_blend_operation;
		bool m_depth_test;
		bool m_blending;
		bool m_line_smooth;
		bool m_multisample;
		bool m_polygon_smooth;
		bool m_wireframe;
		bool m_use_diffuse_texture;
		bool m_use_text_texture;
		bool m_enable_shadows;
		bool m_enable_lighting;

		float m_line_width;
		int m_diffuse_slot_0;
		int m_diffuse_slot_1;
		int m_normal_slot;
		int m_text_slot;
		int m_height_map_slot;

		//	this pointers should not be deleted in destructor
		std::vector<Virtual::Light*> m_lights;
		AbstractRenderPolicy* m_rc;
		Virtual::Material* m_material;
		Virtual::Camera* m_camera;
		Virtual::Armature* m_armature;
		Virtual::Terrain* m_terrain;
		Virtual::TerrainObserver* m_terrain_observer;
		//	this pointers should not be deleted in destructor
	};	
}

#endif	//	_H_PUNK_RENDER_STATE