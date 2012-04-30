#ifndef _H_PUNK_SOLID_RENDER
#define _H_PUNK_SOLID_RENDER

#include "../math/mat4.h"

#include "vertex_array_object.h"
#include "render.h"

namespace Render
{
	class SolidRender : public AbstractRender
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
			const VertexArrayObject* m_vertex_array_object;
			
			void Set(const VertexArrayObject* vao, 
				const Math::mat4& world_transform, 
				const Math::mat4& view_transformconst,
				const Math::mat4& projection_transform,
				Math::vec4& color);

			static Parameters* Create();
			void Release();
		};

	private:
		
		ShaderProgram* m_shader_program;

		GLint m_vertex_attribute;
		GLint m_proj_view_world_uniform;
		GLint m_diffuse_color_uniform;

	protected:

		SolidRender();
		SolidRender(const SolidRender&);
		SolidRender& operator = (const SolidRender&);

	public:

		static SolidRender* GetRender();
		virtual ~SolidRender();
		virtual void Render(void* parameters);
		virtual void BindShaderData();

	};
}

#endif