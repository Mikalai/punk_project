#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../system/state_manager.h"
#include "../../math/clip_space.h"

namespace Virtual { class LightSet; }
namespace Virtual { class Light; }
namespace Virtual { class Material; }
namespace Virtual { class Camera; } 
namespace Virtual { class Armature; }

namespace OpenGL
{
	class AbstractRenderPolicy; 
	class AbstractRenderPolicyParameters; 
	class TextureContext; 
	class RenderPass; 

	class CoreState
	{
	public:
		enum BlendOperation { BLEND_SRC_ONE_MINUS_ALPHA };

		CoreState();

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

		System::Proxy<Virtual::Armature> m_armature;
		System::Proxy<Virtual::Camera> m_camera;		
		System::Proxy<Virtual::Material> m_current_material;
		System::Proxy<TextureContext> m_tc;
		//System::Proxy<RenderPass> m_pass;					
		std::vector<System::Proxy<Virtual::Light>> m_current_light_set;
		System::Proxy<AbstractRenderPolicy> m_render_policy;
		Math::ClipSpace m_clip_space;
		
		BlendOperation m_blend_operation;
		bool m_depth_test;
		bool m_blending;
		bool m_line_smooth;
		bool m_multisample;
		bool m_polygon_smooth;
		bool m_wireframe;
		bool m_use_diffuse_texture;

		float m_line_width;
		int m_diffuse_slot;
		int m_normal_slot;
		int m_text_slot;
	};	
}

#endif	//	_H_PUNK_RENDER_STATE