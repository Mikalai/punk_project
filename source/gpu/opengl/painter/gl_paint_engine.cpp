#include "gl_paint_engine.h"
#include "../../../math/rect.h"
#include "../render_targets/module.h"
#include "../textures/module.h"
#include "../../../system/module.h"
#include "../../common/module.h"
#include "../renderable/module.h"

#define STATE m_states.CurrentState()->Get()

namespace GPU
{
	namespace OpenGL
	{
		struct OpenGLPaintEngine::OpenGLPaintEngineImpl
		{
			RenderTargetTexture* m_rt;
			System::StateManager<GPU::CoreState> m_states;
			GPU::AbstractRenderPolicy* m_solid_rc;

			OpenGLPaintEngineImpl()
				: m_rt(new RenderTargetTexture)
			{
				auto props = GPU::OpenGL::RenderTargetTexture::RenderTargetTextureProperties();
				
				m_rt->Init(&props);
				m_rt->SetClearColor(0.5f, 0.2f, 0.1f, 1.0f);							

				m_solid_rc = GPU::AbstractRenderPolicy::find(GPU::RC_SOLD_3D);
			}

			~OpenGLPaintEngineImpl()
			{
				delete m_rt;
				m_rt = nullptr;
			}

			RenderTargetTexture* GetRenderTarget()
			{
				return m_rt;
			}

			void SetSurfaceSize(int width, int height)
			{
				m_rt->SetViewport(0, 0, width, height);
			}

			bool Begin(PaintDevice* device) 
			{
				m_rt->Activate();
				return true;
			}

			void DrawLines(const Math::Line2D* lines, size_t count) 
			{}

			void DrawRects(const Math::Rect* rects, size_t count) 
			{}

			void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle) 
			{}

			void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle) 
			{}

			void DrawPoint(float x, float y) 
			{}

			void DrawEllipse(float xc, float yc, float major_axis, float minor_axis) 
			{}

			void RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
			{
				m_states.Push();
				//	shift quadSTATE
				STATE.m_local = Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1);
				STATE.m_projection = Math::mat4::CreateIdentity();
				STATE.m_view = Math::mat4::CreateIdentity();
				STATE.m_diffuse_color = color;
				STATE.m_depth_test = false;
				m_solid_rc->Begin();
				m_solid_rc->BindParameters(STATE);
				GPU::OpenGL::QuadObject::Instance()->Bind(m_solid_rc->GetRequiredAttributesSet());
				GPU::OpenGL::QuadObject::Instance()->Render();
				GPU::OpenGL::QuadObject::Instance()->Unbind();
				m_solid_rc->End();
				m_states.Pop();
			}

			void DrawRect(const Math::Rect& rect) 
			{
				float max_width = (float)m_rt->GetColorBuffer()->GetWidth();
				float max_height = (float) m_rt->GetColorBuffer()->GetHeight();			

				RenderQuad(rect.GetX() / max_width, rect.GetY() / max_height, 
					rect.GetWidth() / max_width, rect.GetHeight() / max_height, Math::vec4(0, 0, 1, 1));
			}

			bool End() 
			{
				m_rt->Deactivate();
				return true;
			}
		};

		OpenGLPaintEngine::OpenGLPaintEngine()
			: impl(new OpenGLPaintEngineImpl)
		{
		}

		OpenGLPaintEngine::~OpenGLPaintEngine()
		{
			delete impl;
			impl = nullptr;
		}

		RenderTargetTexture* OpenGLPaintEngine::GetRenderTarget()
		{
			return impl->GetRenderTarget();
		}

		bool OpenGLPaintEngine::Begin(PaintDevice* device) 
		{
			return impl->Begin(device);
		}

		void OpenGLPaintEngine::DrawLines(const Math::Line2D* lines, size_t count) 
		{
			impl->DrawLines(lines, count);
		}

		void OpenGLPaintEngine::DrawRects(const Math::Rect* rects, size_t count) 
		{
			impl->DrawRects(rects, count);
		}

		void OpenGLPaintEngine::DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle)
		{
			impl->DrawArc(xc, yc, width, height, start_angle, span_angle);
		}

		void OpenGLPaintEngine::DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle) 
		{
			impl->DrawChord(xc, yc, width, height, start_angle, span_angle);
		}

		void OpenGLPaintEngine::DrawPoint(float x, float y) 
		{
			impl->DrawPoint(x, y);
		}

		void OpenGLPaintEngine::DrawEllipse(float xc, float yc, float major_axis, float minor_axis) 
		{
			impl->DrawEllipse(xc, yc, major_axis, minor_axis);
		}

		void OpenGLPaintEngine::DrawRect(const Math::Rect& rect) 
		{
			impl->DrawRect(rect);
		}

		bool OpenGLPaintEngine::End() 
		{
			return impl->End();
		}

		void OpenGLPaintEngine::SetSurfaceSize(int width, int height)
		{
			impl->SetSurfaceSize(width, height);
		}
	}
}