#ifndef _H_PUNK_OPENGL_TEXT_TEXTURE
#define _H_PUNK_OPENGL_TEXT_TEXTURE

#include "../../config.h"
#include "../../system/object.h"
#include "texture2d.h"

namespace OpenGL
{
	class PUNK_ENGINE TextSurface : public System::Object
	{
	public:
		enum TextHorizontalAlignment { HORIZONTAL_LEFT, HORIZONTAL_RIGHT, HORIZONTAL_CENTER, HORIZONTAL_WIDTH };
		enum TextVerticalAlignment { VERTICAL_TOP, VERTICAL_BOTTOM, VERTICAL_CENTER };
		enum TextDirection { DIRECTION_HORIZONTAL, DIRECTION_VERTICAL };

		TextSurface();
		void SetSize(int width, int height);
		void SetAutoWrapFlag(bool value) { m_auto_wrap = value; }
		bool GetAutoWrapFlag(bool value) { return m_auto_wrap; }
		bool SetText(const System::string& text);
		const System::string& GetText() const { return m_text; }
		System::Proxy<Texture2D> GetTexture() { return m_texture; }
		const System::Proxy<Texture2D> GetTexture() const { return m_texture; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		void SetFont(const System::string& font);
		const System::string& GetFont() const { return m_font; }

		void SetTextSize(int size);
		int GetTextSize() const { return m_font_size; }

		void SetHorizontalAlignment(TextHorizontalAlignment value) { m_halignment = value; RenderTextToTexture(); }
		TextHorizontalAlignment GetHorizontalAlignment() const { return m_halignment; }

		void SetVerticalAlignment(TextVerticalAlignment value) { m_valignment = value; RenderTextToTexture(); }
		TextVerticalAlignment GetVerticalAlignment() const { return m_valignment; }

	private:
		TextHorizontalAlignment m_halignment;
		TextVerticalAlignment m_valignment;
		bool m_auto_wrap;
		int m_font_size;
		System::string m_text;		
		System::string m_font;
		System::Proxy<Texture2D> m_texture;
		
		int CalculateTextXOffset(const System::string& text);
		int CalculateTextYOffset(const System::string& text);
		bool RenderTextToTexture();
	};
}

#endif	//	_H_PUNK_OPENGL_TEXT_TEXTURE
