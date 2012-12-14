#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../system/smart_pointers/proxy.h"
#include "../../math/clip_space.h"

namespace Virtual { class LightSet; }
namespace Virtual { class Material; }
namespace Virtual { class Camera; } 

namespace OpenGL
{
	class AbstractRenderPolicy; 
	class AbstractRenderPolicyParameters; 
	class TextureContext; 
	class RenderPass; 

	class State
	{
	public:

		Math::mat4 m_local;		
		Math::mat4 m_projection;
		Math::mat4 m_view;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_text_color;
		Math::vec4 m_no_diffuse_texture_color;
		Math::vec4 m_specular_color;
		Math::vec4 m_specular_factor;		
		Math::vec3 m_camera_position;
		Math::mat2 m_texture_matrix;

		System::Proxy<Virtual::Camera> m_camera;		
		System::Proxy<Virtual::Material> m_current_material;
		System::Proxy<TextureContext> m_tc;
		//System::Proxy<RenderPass> m_pass;					
		System::Proxy<Virtual::LightSet> m_current_light_set;
		System::Proxy<AbstractRenderPolicy> m_render_policy;
		Math::ClipSpace m_clip_space;

		bool m_depth_test;
		bool m_blending;
		bool m_line_smooth;
		bool m_multisample;
		bool m_polygon_smooth;

		int m_diffuse_slot;
		int m_normal_slot;
		int m_text_slot;
	};

	class StateManager
	{
	public:
		
		StateManager() { Init(); }
		~StateManager() { Clear(); }

		System::Proxy<State> CurrentState() { return m_current_state; }

		void Push();
		bool Pop();

	private:

		void Init();
		void Clear();

		System::Proxy<State> m_current_state;
		std::stack<System::Proxy<State>> m_states;
	};

}

#endif	//	_H_PUNK_RENDER_STATE