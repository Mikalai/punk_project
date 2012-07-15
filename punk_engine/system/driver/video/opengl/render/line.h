#ifndef _H_PUNK_OPENGL_LINE
#define _H_PUNK_OPENGL_LINE

#include "../config.h"
#include "../render_context/shader.h"
#include "../render_context/render_context.h"
#include "../vertex_array_object.h"
#include "../../../../../math/math.h"

namespace OpenGL
{
	class MODULE_OPENGL Line
	{
		std::auto_ptr<Shader> m_vertex_shader;
		std::auto_ptr<Shader> m_fragment_shader;
		std::auto_ptr<RenderContext> m_render;
		std::auto_ptr<VertexArrayObject> m_vao;
	public:
		Line() { Init(); }
		~Line() { Clear(); }
		void SetLocalTransform(const Math::mat4& value);
		void SetViewTranform(const Math::mat4& value);
		void SetProjectionTransform(const Math::mat4& value);
		void SetColor(float r, float g, float b, float a);
		void SetColor(const Math::vec4& color);
		void Draw(const Math::vec3& p1, const Math::vec3& p2);
	private:
		void Init();
		void Clear();
		void InitVAO();
	private:
		Math::mat4 m_local;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::vec4 m_color;

		unsigned m_proj_view_world_uniform;
		unsigned m_start_uniform;
		unsigned m_end_uniform;
		unsigned m_color_uniform;
	};
}

#endif
