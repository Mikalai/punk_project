#ifndef _H_PUNK_QUAD
#define _H_PUNK_QUAD

#include <queue>
//#include "../abstract_render.h"
//#include "../../driver/video/driver.h"

namespace Render
{
	class QuadRender : public ::Render::AbstractRender
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
			float m_x, m_y, m_width, m_height;
			float m_color[4];						
			
			void Set(float x, float y, float width, float height, float* color);
			static Parameters* Create();
			void Release();
		};

	private:
		struct Vertex
		{
			float x, y;
			static const unsigned PositionOffset = 0;
		};
		
	protected:

		GLint m_vertex_attribute;
		GLint m_proj_view_world_uniform;
		GLint m_diffuse_color_uniform;
		GLint m_radiusUniform;
		int m_indexCount;
		int m_vertexCount;
		ShaderProgram* m_program;
		GLuint m_vertexBuffer;
		GLuint m_indexBuffer;
		GLuint m_vao;

		QuadRender();
		QuadRender(const QuadRender&);
		QuadRender& operator = (const QuadRender&);

	public:
		static QuadRender* GetRender();
		virtual ~QuadRender();
		virtual void Render(void* parameters);
		virtual void BindShaderData();
	};
}

#endif	// _H_PUNK_QUAD