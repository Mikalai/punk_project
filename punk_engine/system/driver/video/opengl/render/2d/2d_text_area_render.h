/*
File: 2d_text_area.h
Author: Mikalai Abramau
Desc: class for rendering a rectangle text areas, part of punk_engine
*/

#ifndef _H_PUNK_2D_TEXT_AREA
#define _H_PUNK_2D_TEXT_AREA

namespace OpenGL
{
	class TextAreaRender : public AbstractRender
	{
	public:
		struct Parameters
		{
		private:
			static std::queue<Parameters*> parametersPool;
		public:
			float m_x, m_y, m_width, m_height;
			float m_back_color[4];
			Driver::Texture2D* m_texture;

			void Set(float x, float y, float width, float height, float* color, Driver::Texture2D* texture);

			static Parameters* Create();
			void Release();
		};

	private:
		struct Vertex
		{
			float x, y;
			float tx, ty;
			static const unsigned PositionOffset = 0;
			static const unsigned TextureOffset = 2*sizeof(float);
		};

		TextAreaRender(const TextAreaRender&);

	protected:		

		GLint m_vertex_attribute;
		GLint m_textureVertexAttrib;

		GLint m_proj_view_world_uniform;
		GLint m_diffuse_color_uniform;
		GLint m_baseMapUniform;

		int m_indexCount;
		int m_vertexCount;
		ShaderProgram* m_program;
		GLuint m_vertexBuffer;
		GLuint m_indexBuffer;
		GLuint m_vao;

		TextAreaRender();
	private:
		void RenderTextToTexture(int size, const char* text);
	public:
		
		static TextAreaRender* GetRender();

		virtual void Render(void* parameters);
		virtual void BindShaderData();
	};
}


#endif //_H_PUNK_2D_TEXT_AREA