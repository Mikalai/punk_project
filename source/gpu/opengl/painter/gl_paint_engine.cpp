#include "gl_paint_engine.h"
#include "../../../math/rect.h"
#include "../render_targets/module.h"
#include "../textures/module.h"
#include "../../../system/module.h"
#include "../../common/module.h"
#include "../renderable/module.h"
#include "../../../utility/module.h"
#include "../../common/primitives/module.h"

#define STATE m_states.CurrentState()->Get()

namespace Gpu
{
	namespace OpenGL
	{
		struct OpenGLPaintEngine::OpenGLPaintEngineImpl
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color> VertexType;

			VideoDriver* m_driver;
//			RenderTargetTextureColorDepth* m_rt;
			//System::StateManager<GPU::CoreState> m_states;
			Gpu::AbstractRenderPolicy* m_solid_rc;
			Math::vec4 m_color;
			Math::vec4 m_fill_color;
			Gpu::TextureContext* m_tc;
			Gpu::AbstractRenderPolicy* m_gui_rc;
			Gpu::AbstractRenderPolicy* m_painter_rc;
			Utility::FontBuilder m_font_builder;

			Gpu::Lines<VertexType> m_lines_vao;
			Gpu::QuadObject m_quad;

			const Texture2D* m_fill_texture;
			bool m_use_border;
			bool m_use_fill;
			bool m_lines_modified;
			System::string m_font_name;
			int m_font_size;

			std::vector<VertexType> m_lines;

			OpenGLPaintEngineImpl(VideoDriver* driver)
				: m_driver(driver)
//				, m_rt(nullptr)
				, m_lines_vao(driver)
				, m_quad(driver)
			{
				try
				{
					//auto props = GPU::OpenGL::RenderTargetTexture::RenderTargetTextureProperties();

					//m_rt->Init(&props);
					//m_rt->SetClearColor(0.5f, 0.2f, 0.1f, 1.0f);

					m_solid_rc = Gpu::AbstractRenderPolicy::find(Gpu::RenderPolicySet::Solid3D);
					m_gui_rc = Gpu::AbstractRenderPolicy::find(Gpu::RenderPolicySet::GUI);
					m_painter_rc = Gpu::AbstractRenderPolicy::find(Gpu::RenderPolicySet::Painter);

					m_tc = new TextureContext;

					m_use_fill = true;
					m_use_border = true;

					m_color.Set(0,0,1,0.5f);
					m_fill_color.Set(1,1,1,0.5f);
					m_font_size = 14;
					m_font_name = L"times.ttf";
				}
				catch(System::PunkException& e)
				{
					out_error() << e.ToString() << std::endl;
				}
			}

			~OpenGLPaintEngineImpl()
			{
//				delete m_rt;
//				m_rt = nullptr;

				delete m_tc;
				m_tc = nullptr;
			}

//			RenderTargetTextureColorDepth* GetRenderTarget()
//			{
//				return m_rt;
//			}

			void SetSurfaceSize(int, int)
			{
				//	m_rt->SetViewport(Math::Rect(0, 0, (float)width, (float)height));
			}

			bool Begin(PaintDevice*)
			{
				//	m_rt->Activate();
				return true;
			}

			void CookCPULineBuffer(const Math::Line2D* lines, size_t count)
			{
                float max_width = 0;//(float)m_rt->GetColorBuffer()->GetWidth();
                float max_height = 0;//(float) m_rt->GetColorBuffer()->GetHeight();

				m_lines_modified = true;
				for (size_t i = 0; i < count; ++i)
				{
					VertexType va;
					const Math::vec2& a = lines[i].Origin();
					va.m_position.Set(2.0f * a.X() / max_width - 1.0f, 2.0f * a.Y() / max_height - 1.0f, 0, 1.0f);
					va.m_flag.Set(0,0,0,0);
					va.m_texture0.Set(0,0,0,0);
					va.m_color = m_color;

					m_lines.push_back(va);

					VertexType vb;
					const Math::vec2& b = lines[i].Destination();
					vb.m_position.Set(2.0f * b.X() / max_width - 1.0f, 2.0f * b.Y() / max_height - 1.0f, 0, 1.0f);
					vb.m_flag.Set(0,0,0,0);
					vb.m_texture0.Set((a-b).Dot(Math::vec2(1, 0)), (a-b).Dot(Math::vec2(0, 1)), 0, 0);
					vb.m_color = m_color;

					m_lines.push_back(vb);
				}
			}

			void CookGPULinesBuffer()
			{
				if (m_lines_modified && !m_lines.empty())
				{
					m_lines_vao.Cook(m_lines);
					m_lines.clear();
					m_lines_modified = false;
				}
			}

			void DrawLines(const Math::Line2D* lines, size_t count)
			{
				CookCPULineBuffer(lines, count);
				CookGPULinesBuffer();

//				m_states.CurrentState()->Get().m_use_diffuse_texture = false;
//				m_states.CurrentState()->Get().m_use_text_texture = false;
//				m_states.CurrentState()->Get().render_state->m_enable_wireframe = false;
//				m_states.CurrentState()->Get().m_enable_blending = true;
//				m_states.CurrentState()->Get().m_diffuse_color = m_color;

				m_tc->Bind();
				m_painter_rc->Begin();
//				m_painter_rc->BindParameters(STATE);

                //if (m_lines_vao.HasData())
				{
					m_lines_vao.Bind(m_painter_rc->GetRequiredAttributesSet());
					m_lines_vao.Render();
					m_lines_vao.Unbind();
				}

				m_painter_rc->End();
				m_painter_rc->End();
				m_tc->Unbind();
			}

			void DrawRects(const Math::Rect*, size_t)
			{}

			void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle)
			{
				(void)xc; (void)yc; (void)width; (void)height; (void)start_angle; (void)span_angle;
			}

			void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle)
			{
				(void)xc; (void)yc; (void)width; (void)height; (void)start_angle; (void)span_angle;
			}

			void DrawPoint(float x, float y)
			{
				(void)x; (void)y;
			}

			void DrawEllipse(float xc, float yc, float major_axis, float minor_axis)
			{
				(void)xc; (void)yc; (void)major_axis; (void)minor_axis;
			}

			void RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
			{
//				m_states.Push();
				//	shift quadSTATE
//				STATE.m_world = Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1);
//				STATE.m_projection = Math::mat4::CreateIdentity();
//				STATE.m_view = Math::mat4::CreateIdentity();
//				STATE.m_diffuse_color = color;
//				STATE.m_depth_test = false;
//				STATE.m_enable_blending = true;
				m_solid_rc->Begin();
//				m_solid_rc->BindParameters(STATE);
				m_quad.Bind(m_solid_rc->GetRequiredAttributesSet());
				m_quad.Render();
				m_quad.Unbind();
				m_solid_rc->End();
//				m_states.Pop();
			}

			void DrawRect(const Math::Rect& rect)
			{
                float max_width = 0; //(float)m_rt->GetColorBuffer()->GetWidth();
                float max_height = 0; //(float) m_rt->GetColorBuffer()->GetHeight();

				if (m_use_fill)
				{
					RenderQuad(rect.GetX() / max_width, rect.GetY() / max_height,
							   rect.GetWidth() / max_width, rect.GetHeight() / max_height, m_fill_color);
				}

				if (m_use_border)
				{
					std::vector<Math::Line2D> lines;
					lines.push_back(Math::Line2D(Math::vec2(rect.GetX(), rect.GetY()),
												 Math::vec2(rect.GetX() + rect.GetWidth(), rect.GetY())));
					lines.push_back(Math::Line2D(Math::vec2(rect.GetX()+rect.GetWidth(), rect.GetY()),
												 Math::vec2(rect.GetX() + rect.GetWidth(), rect.GetY() + rect.GetHeight())));
					lines.push_back(Math::Line2D(Math::vec2(rect.GetX() + rect.GetWidth(), rect.GetY() + rect.GetHeight()),
												 Math::vec2(rect.GetX(), rect.GetY() + rect.GetHeight())));
					lines.push_back(Math::Line2D(Math::vec2(rect.GetX(), rect.GetY() + rect.GetHeight()),
												 Math::vec2(rect.GetX(), rect.GetY())));
					DrawLines(&lines[0], lines.size());
				}
			}

			bool End()
			{
//				m_rt->Deactivate();
				return true;
			}

			void SetColor(const Math::vec4& value)
			{
				m_color = value;
			}

			void SetColor(float r, float g, float b, float a)
			{
				m_color.Set(r, g, b, a);
			}

			void SetFillColor(const Math::vec4& value)
			{
				m_fill_color = value;
			}

			void SetFillColor(float r, float g, float b, float a)
			{
				m_fill_color.Set(r, g, b, a);
			}

			void SetFillTexture(const Texture2D* value)
			{
				m_fill_texture = value;
			}

			void SetLineWidth(float value)
			{
//				STATE.m_line_width = value;
			}

			void SetPointSize(float value)
			{
//				STATE.m_point_size = value;
			}

			void RenderText(float x, float y, const System::string& text, const Math::vec4& color)
			{
                float max_width = 0;//(float)m_rt->GetColorBuffer()->GetWidth();
                float max_height = 0;//(float) m_rt->GetColorBuffer()->GetHeight();

				m_font_builder.SetCurrentFace(m_font_name);
				m_font_builder.SetCharSize(m_font_size, m_font_size);
                int len = m_font_builder.CalculateLength(text);
                int h = m_font_builder.CalculateHeight(text);
                Gpu::TextSurface s(len, h,  m_driver);
				s.SetTextSize(m_font_size);
				s.SetSize(len, h);
				s.SetText(text);

//				m_states.Push();
				float width = 2.0f * len / max_width;
				float height = 2.0f * h / max_height;
				//	shift quad
//				STATE.m_world = Math::mat4::CreateTranslate( 2.0f * x / max_width - 1.0f, 2.0f * y / max_height - 1.0f, 0) * Math::mat4::CreateScaling(width, height, 1.0f);
//				STATE.m_projection = Math::mat4::CreateIdentity();
//				STATE.m_view = Math::mat4::CreateIdentity();
//				STATE.m_diffuse_slot_0 = 0;
//				STATE.m_diffuse_color = color;
//				STATE.m_no_diffuse_texture_color.Set(1,1,1,0);
//				//STATE.m_texture_matrix = Math::mat2::CreateMirrorX();
//				STATE.m_text_slot= 0;

				m_tc->SetTexture(0, s.GetTexture());
				m_tc->SetTexture(1, nullptr);
				m_tc->Bind();
				m_gui_rc->Begin();
//				m_gui_rc->BindParameters(STATE);
				m_quad.Bind(m_gui_rc->GetRequiredAttributesSet());
				m_quad.Render();
				m_quad.Unbind();
				m_gui_rc->End();
				m_tc->Unbind();
//				m_states.Pop();
			}

			void DrawString(float x, float y, const System::string& text)
			{
				RenderText(x, y, text, m_color);
			}

			void EnableFill(bool value)
			{
				m_use_fill = value;
			}

			void EnableBorder(bool value)
			{
				m_use_border = value;
			}

			void SetFontName(const System::string& font)
			{
				m_font_name = font;
			}

			void SetFontSize(int size)
			{
				m_font_size = size;
			}

		};

		OpenGLPaintEngine::OpenGLPaintEngine(VideoDriver* driver)
			: impl(new OpenGLPaintEngineImpl(driver))
		{
		}

		OpenGLPaintEngine::~OpenGLPaintEngine()
		{
			delete impl;
			impl = nullptr;
		}

//		RenderTargetTextureColorDepth* OpenGLPaintEngine::GetRenderTarget()
//		{
//			return impl->GetRenderTarget();
//		}

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

		void OpenGLPaintEngine::SetColor(const Math::vec4& value)
		{
			impl->SetColor(value);
		}

		void OpenGLPaintEngine::SetColor(float r, float g, float b, float a)
		{
			impl->SetColor(r, g, b, a);
		}

		void OpenGLPaintEngine::SetFillColor(const Math::vec4& value)
		{
			impl->SetFillColor(value);
		}

		void OpenGLPaintEngine::SetFillColor(float r, float g, float b, float a)
		{
			impl->SetFillColor(r, g, b, a);
		}

		void OpenGLPaintEngine::SetFillTexture(const Texture2D* value)
		{
			impl->SetFillTexture(value);
		}

		void OpenGLPaintEngine::SetLineWidth(float value)
		{
			impl->SetLineWidth(value);
		}

		void OpenGLPaintEngine::SetPointSize(float value)
		{
			impl->SetPointSize(value);
		}

		void OpenGLPaintEngine::DrawString(float x, float y, const System::string& text)
		{
			impl->DrawString(x, y, text);
		}

		void OpenGLPaintEngine::EnableFill(bool value)
		{
			impl->EnableFill(value);
		}

		void OpenGLPaintEngine::EnableBorder(bool value)
		{
			impl->EnableBorder(value);
		}

		void OpenGLPaintEngine::SetFontName(const System::string& font)
		{
			impl->SetFontName(font);
		}

		void OpenGLPaintEngine::SetFontSize(int size)
		{
			impl->SetFontSize(size);
		}
	}
}
