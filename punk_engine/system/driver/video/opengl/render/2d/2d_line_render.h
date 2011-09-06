#ifndef _H_PUNK_2D_LINE_RENDER
#define _H_PUNK_2D_LINE_RENDER

#include <queue>
#include "../../driver/video/driver.h"
#include "../abstract_render.h"

namespace Render
{
	class LineRender : public AbstractRender
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
			float m_p1[2];
			float m_p2[2];
			float m_color[4];

			void Set(float x1, float y1, float x2, float y2, float* color);
			static Parameters* Create();
			void Release();
		};
	private:
		struct Vertex
		{
			float x, y;
			static const unsigned PositionOffset = 0;
		};

		unsigned m_vertex_attribute;
		unsigned m_diffuse_color_uniform;
		unsigned m_p1Uniform;
		unsigned m_p2Uniform;
		unsigned m_widthUniform;
		unsigned m_heightUniform;
		int m_indexCount;
		int m_vertexCount;
		ShaderProgram* m_program;
		unsigned m_vertexBuffer;
		unsigned m_indexBuffer;
		unsigned m_vao;

	public:
		LineRender();
		~LineRender();
		virtual void Render(void* p);
		virtual void BindShaderData();

		static LineRender* GetRender();
	};
}

#endif