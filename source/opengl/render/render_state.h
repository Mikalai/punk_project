#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../system/smart_pointers/proxy.h"
#include "../../math/clip_space.h"

namespace Virtual { class LightSet; }
namespace Virtual { class Material; }
namespace Virtual { namespace Cameras { class Camera; } }

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
		
		System::Proxy<Virtual::Cameras::Camera> m_camera;		
		System::Proxy<Virtual::Material> m_current_material;
		System::Proxy<TextureContext> m_tc;
		System::Proxy<RenderPass> m_pass;					
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