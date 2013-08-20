#ifndef _H_PUNK_RENDER_STATE
#define _H_PUNK_RENDER_STATE

#include <vector>
#include <stack>
#include "../../config.h"
#include "../../math/module.h"
#include "../../system/state_manager.h"
#include "../../system/poolable.h"
#include "../../virtual/interface.h"
#include "lighting/module.h"
#include "blending/module.h"
#include "fog/module.h"
#include "material/module.h"
#include "config.h"
#include "shadow_model.h"

namespace Gpu
{
	class CoreState;
	class Texture2D;
    class Texture2DArray;
	class AbstractRenderPolicy;

	/**
	 * @brief The BaseState class. It has a very specific purpose.
	 * Used only with gpu state for rendering. Holds current index of the
	 * of the instance of the render state. It is guaranteed if during
	 * next state created from previous state.
	 */
    class PUNK_ENGINE_API BaseState
	{
	public:
        BaseState() : m_index(0), m_count(1), m_total(0) {}

		BaseState(const BaseState& state)
		{
			m_total++;
            m_count = 1;
			m_index = m_total;
			state.m_total = m_total;
		}

		unsigned Inc() { return ++m_count; }
		unsigned Dec() { return --m_count; }

	private:
		///	Unique index of current state
		unsigned m_index;
        ///	Holds count of copies of current instance.
        unsigned m_count;
		///	Holds "total" count of instances created during current frame
		mutable unsigned m_total;		

		/// Copy operator is forbidden forever
		BaseState& operator = (const BaseState&) = delete;

	};

    class PUNK_ENGINE_API ViewState final : private BaseState, public System::Poolable<ViewState>
	{
	public:
		Math::mat4 m_projection;
		Math::mat4 m_view;
		Math::ClipSpace m_clip_space;
		Math::vec3 m_camera_position;
        Math::vec4 m_far_distances;
        float m_zfar;
        float m_znear;

		friend class CoreState;
	};

    class PUNK_ENGINE_API LightState final : private BaseState, public System::Poolable<LightState>
	{
	public:
        LightState();
		LightModel m_light_model;
		//	this pointers should not be deleted in destructor
		LightParameters m_lights[MAX_LIGHTS];
        unsigned m_used_lights;

		friend class CoreState;
	};

    class PUNK_ENGINE_API RenderState final : private BaseState, public System::Poolable<RenderState>
	{
	public:
		RenderState();

		BlendFunction m_blend_src;
		BlendFunction m_blend_dst;
		Math::vec4 m_blend_color;
		Math::vec4 m_clear_color;

		//	added on 15.05.2013
		FogDescription m_fog;
        ShadowModel m_shadow_model;
        Math::ivec2 m_shadow_map_size;

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
		bool m_enable_texture;
		bool m_enable_font_rendering;
		bool m_enable_vertex_color;
		bool m_enable_text_rendering;
		bool m_enable_skinning;
		bool m_enable_terrain;
		bool m_enable_water;
        bool m_enable_bounding_box_rendering;
        bool m_enable_bounding_sphere_rendering;
        bool m_enable_navi_mesh_rendering;
        //bool m_enable_bump_maping_shading;
		bool m_render_depth;        
		float m_clear_depth;

		float m_line_width;
		float m_point_size;

		friend class CoreState;
	};

    class PUNK_ENGINE_API BatchState final : private BaseState, public System::Poolable<BatchState>
	{
	public:
        BatchState();

		Math::mat4 m_world;
		Math::mat4 m_local;
		//	corresponds to the part of the world matrix of the skin mesh
		Math::mat4 m_armature_world;
		Math::mat4 m_bone_world;
		Math::mat4 m_texture_matrix;
		Math::vec2 m_terran_position;
        //  bounding volumes in local position
        Math::BoundingBox m_bbox;
        Math::BoundingSphere m_bsphere;

		Material m_material;

		int m_terrain_level;
		int m_terrain_i;
		int m_terrain_j;
		int m_terrain_slices;

        int m_used_bones_count;
        Math::mat4 m_bone_matrix[MAX_BONES];

		bool m_cast_shadows;
		bool m_receive_shadows;

		friend class CoreState;
	};

    class PUNK_ENGINE_API TextureState final : private BaseState, public System::Poolable<TextureState>
	{
	public:
		TextureState();

        Texture2D* m_diffuse_map[4] = {nullptr, nullptr, nullptr, nullptr};
        Texture2D* m_normal_map = nullptr;
        Texture2D* m_height_map = nullptr;
        Texture2D* m_specular_map = nullptr;
        Texture2D* m_text_map = nullptr;
        Texture2D* m_shadow_map = nullptr;
        Texture2DArray* m_texture_array = nullptr;
        int m_texture_array_diffuse_map_layer[4] = {-1, -1, -1, -1};
        int m_texture_array_normal_map_layer = -1;
        int m_texture_array_height_map_layer = -1;
        int m_texture_array_specular_map_layer = -1;
        int m_texture_array_text_map_layer = -1;
        int m_texture_array_shadow_map_layer[4] = {-1, -1, -1, -1};

        int m_diffuse_slot[4] = {-1, -1, -1, -1};
        int m_normal_map_slot = -1;
        int m_text_map_slot = -1;
        int m_height_map_slot = -1;
        int m_texture_array_slot = -1;
        int m_shadow_map_slot = -1;
        int m_specular_map_slot = -1;

		friend class CoreState;

	};

    class PUNK_ENGINE_API CoreState final : private BaseState, public System::Poolable<CoreState>
	{
	public:		
        static const unsigned VIEW_STATE	= 0x0000001;
        static const unsigned LIGHT_STATE	= 0x0000002;
        static const unsigned RENDER_STATE	= 0x0000004;
        static const unsigned BATCH_STATE	= 0x0000008;
        static const unsigned TEXTURE_STATE = 0x0000010;
        static const unsigned ALL_STATES	= 0xFFFFFFF;
        static const unsigned NO_STATES		= 0x0000000;

		CoreState();
		CoreState(unsigned mode, CoreState* state);
		~CoreState();

		ViewState* view_state;
		LightState* light_state;
		RenderState* render_state;
		BatchState* batch_state;
		TextureState* texture_state;

		/**
		 * Color buffer is a core state, because typically it is before rendering
		 * and not changed until the end of rendering
		 */
		Texture2D* m_color_buffer;
		Texture2D* m_depth_buffer;

        Texture2DArray* m_shadow_maps;

		/**
		 * @brief m_active_rendering
		 * This flag is active when Frame::BeginRendering was called.
		 * It will be reset when EndRendering is called. Some functions
		 * can't be called during active rendering. For example SetRenderTarget.
		 */
		bool m_active_rendering;

		//	this pointers should not be deleted in destructor
		CoreState* Clone(unsigned mode);

		CoreState(const CoreState&) = delete;
		CoreState& operator = (const CoreState&) = delete;

        friend class Frame;
	};	
}

#endif	//	_H_PUNK_RENDER_STATE
