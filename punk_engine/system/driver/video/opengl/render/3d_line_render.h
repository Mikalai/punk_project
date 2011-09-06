#ifndef _H_PUNK_SOLID_RENDER
#define _H_PUNK_SOLID_RENDER

#include "../math/mat4.h"

#include "vertex_array_object.h"
#include "render.h"

namespace Render
{
	class LineRender3D : public AbstractRender
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
			Math::vec4 m_color;						
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

		GLint m_vertexAttrib;
		GLint m_worldViewProjUniform;
		GLint m_diffuseColorUniform;

	protected:

		LineRender3D();
		LineRender3D(const LineRender3D&);
		LineRender3D& operator = (const LineRender3D&);

	public:

		static LineRender3D* GetRender();
		virtual ~LineRender3D();
		virtual void Render(void* parameters);
		virtual void BindShaderData();

	};
}

#endif