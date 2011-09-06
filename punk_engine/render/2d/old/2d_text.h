#ifndef _H_PUNK_2D_TEXT
#define _H_PUNK_2D_TEXT

#include <string>
#include "2d_element.h"

namespace Render
{
	namespace _2D
	{
		class Text : public _2DRenderElement
		{
			struct Vertex
			{
				float x, y;
				float tx, ty;
				static const unsigned PositionOffset = 0;
				static const unsigned TextureOffset = 2*sizeof(float);
			};

			Text(const Text&);

		protected:

			std::string m_text;
			int m_widthInSymbols;
			int m_heightInSymbols;
			int m_symbolSize;
			float m_fontColor[4];
			std::string m_font;

			GLint m_vertexAttrib;
			GLint m_textureVertexAttrib;

			GLint m_worldViewProjUniform;
			GLint m_diffuseColorUniform;
			GLint m_baseMapUniform;
			
			Driver::Video::Texture2D m_texture;

		private:
			void RenderTextToTexture();
		public:
			Text(float x, float y, int widthInSymbols, int heightInSymbols, int symbolSize);
			void SetText(const char* text);


			virtual void Render();
			virtual void BindShaderData();
		};
	}
}

#endif