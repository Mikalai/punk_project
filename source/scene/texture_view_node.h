#ifndef _H_PUNK_SCENE_TEXTURE_VIEW_NODE
#define _H_PUNK_SCENE_TEXTURE_VIEW_NODE

#include "node.h"

namespace GPU { namespace OpenGL { class Texture2D; } }

namespace Scene
{
	class TextureViewNode : public Node
	{
	public:
		TextureViewNode() 
			: m_x(0)
			, m_y(0)
			, m_width(1)
			, m_height(1)
			, m_texture(nullptr)
		{}

		//	x, y, height, width = [0;1]
		void SetSize(float x, float y, float height, float width)
		{
			(m_x = x, m_y = y, m_height = height, m_width = width);
		}

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetWidth() const { return m_width; }
		float GetHeight() const { return m_height; }

		void SetWatchTexture(GPU::OpenGL::Texture2D* value) { m_texture = value; }
		GPU::OpenGL::Texture2D* GetWatchTexture() { return m_texture; }
		
		bool Apply(AbstractVisitor* visitor)
		{
			return visitor->Visit(this);
		}

	private:
		// this pointer should not be delete
		GPU::OpenGL::Texture2D* m_texture;
		float m_x, m_y, m_width, m_height;
	};
}

#endif	//	_H_PUNK_SCENE_TEXTURE_VIEW_NODE