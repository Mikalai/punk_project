#ifndef _H_PUNK_PER_VERTEX_RENDER
#define _H_PUNK_PER_VERTEX_RENDER

#include "abstract_render.h"
#include "../driver/video/driver.h"
#include "../math/math.h"
#include "vertex_array_object.h"

namespace Render
{
	class PerVertexRender : public AbstractRender
	{
	public:
		struct Parameters
		{
		private:
			static std::queue<Parameters*> parametersPool;
			
			Parameters() {}
			Parameters(const Parameters&);
			Parameters& operator = (const Parameters&);

		public:
			Math::mat4 m_world_transform;
			Math::mat4 m_view_transform;
			Math::mat4 m_projection_transform;
			Math::vec4 m_back_color;		
			Math::vec3 m_light_position;
			Math::vec3 m_light_direction;
			const VertexArrayObject* m_vertex_array_object;
			
			void Set(const VertexArrayObject* vao, 
				const Math::mat4& world_transform, 
				const Math::mat4& view_transformconst,
				const Math::mat4& projection_transform,
				const Math::vec4& color,
				const Math::vec3& light_direction,
				const Math::vec3& light_position);

			static Parameters* Create();
			void Release();
		};

	private:
		
		ShaderProgram* m_shader_program;

		GLint m_vertex_attribute;
		GLint m_normalsAttrib;
		GLint m_normalTransformUniform;
		GLint m_proj_view_world_uniform;
		GLint m_diffuse_color_uniform;
		GLint m_viewUniform;
		GLint m_lightDirectionUniform;
		GLint m_lightPositionUniform;

	protected:

		PerVertexRender();
		PerVertexRender(const PerVertexRender&);
		PerVertexRender& operator = (const PerVertexRender&);

	public:

		static PerVertexRender* GetRender();
		virtual ~PerVertexRender();
		virtual void Render(void* parameters);
		virtual void BindShaderData();
	};
}

#endif