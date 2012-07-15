#ifndef _H_PUNK_SOLID_RENDER
#define _H_PUNK_SOLID_RENDER

#include "../math/mat4.h"

#include "vertex_array_object.h"
#include "render.h"

namespace Render
{
	class LineRender
	{
	public:
	
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