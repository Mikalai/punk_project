#ifndef _H_PUNK_OPENGL_PAINTER_IMPL
#define _H_PUNK_OPENGL_PAINTER_IMPL

#include "../../painter/module.h"
#include "../driver/module.h"
#include "../textures/module.h"
#include "../buffers/module.h"
#include "../../../system/state_manager.h"
#include "../../common/gpu_state.h"
#include "../../common/vertex.h"
#include "../../common/texture_context.h"
#include "../../common/primitives/module.h"

namespace GPU
{
	struct Painter::PainterImpl
	{
		typedef Vertex<VertexComponent::Position
			, VertexComponent::Texture0
			, VertexComponent::Flag
			, VertexComponent::Color> VertexType;

		System::StateManager<GPU::CoreState> m_states;
		std::vector<VertexType> m_points;
		bool m_points_modified;
		std::vector<VertexType> m_lines;
		bool m_lines_modified;
		std::vector<VertexType> m_triangles;
		bool m_triangles_modified;
		Points<VertexType> m_points_vao;
		Lines<VertexType> m_lines_vao;
		RenderTarget* m_rt;
		AbstractRenderPolicy* m_rc;
        TextureContext* m_tc;
        PainterImpl(VideoDriver* driver)
            : m_points_modified(false)
            , m_lines_modified(false)
            , m_points_vao(driver)
            , m_lines_vao(driver)
		{
			m_rc = AbstractRenderPolicy::find(RenderPolicySet::Painter);
            m_tc = new TextureContext();
		}

		~PainterImpl()
		{
			safe_delete(m_tc);
		}

        void Begin(RenderTarget*)
		{
//			m_rt = value;
//			if (m_rt)
//				m_rt->Activate();
		}

		void End()
		{
			CookBuffers();
									
			m_states.CurrentState()->Get().m_use_diffuse_texture = false;
			m_states.CurrentState()->Get().m_use_text_texture = false;
			m_states.CurrentState()->Get().m_enable_wireframe = false;
			m_states.CurrentState()->Get().m_enable_blending = true;
			m_states.CurrentState()->Get().m_line_width = 5;
			m_states.CurrentState()->Get().m_diffuse_color.Set(1,0,0,1);

			m_tc->Bind();
			m_rc->Begin();
			m_rc->BindParameters(m_states.CurrentState()->Get());
			if (m_points_vao.HasData())
			{
			m_points_vao.Bind(m_rc->GetRequiredAttributesSet());
			m_points_vao.Render();
			m_points_vao.Unbind();
			}
			if (m_lines_vao.HasData())
			{
				m_lines_vao.Bind(m_rc->GetRequiredAttributesSet());
				m_lines_vao.Render();
				m_lines_vao.Unbind();
			}
			m_rc->End();
			m_rc->End();
			m_tc->Unbind();
			
//			if (m_rt)
//				m_rt->Deactivate();
		}

		void CookBuffers()
		{
			if (m_points_modified)
			{
				m_points_vao.Cook(m_points);
				m_points.clear();
				m_points_modified = false;
			}

			if (m_lines_modified)
			{
				m_lines_vao.Cook(m_lines);
				m_lines.clear();
				m_lines_modified = false;
			}
		}

		void DrawLine(const Math::vec2& a, const Math::vec2& b)
		{
			m_lines_modified = true;
			VertexType va;
			va.m_position.Set(a.X(), a.Y(), 0, 1.0f);
			va.m_flag.Set(0,0,0,0);
			va.m_texture0.Set(0,0,0,0);
			va.m_color = m_states.CurrentState()->Get().m_diffuse_color;

			m_lines.push_back(va);

			VertexType vb;
			vb.m_position.Set(b.X(), b.Y(), 0, 1.0f);
			vb.m_flag.Set(0,0,0,0);
			vb.m_texture0.Set((a-b).Dot(Math::vec2(1, 0)), (a-b).Dot(Math::vec2(0, 1)), 0, 0);
			vb.m_color = m_states.CurrentState()->Get().m_diffuse_color;

			m_lines.push_back(vb);
		}

		void DrawLine(const Math::Line2D& value)
		{
			DrawLine(value.Origin(), value.Destination());
		}

		void DrawPoint(const Math::vec2& point)
		{
			m_points_modified = true;
			VertexType va;
			va.m_position.Set(point.X(), point.Y(), 0, 1.0f);
			va.m_flag.Set(0,0,0,0);
			va.m_texture0.Set(0,0,0,0);
			va.m_color = m_states.CurrentState()->Get().m_diffuse_color;
		}
	};
}

#endif	//	_H_PUNK_OPENGL_PAINTER_IMPL
