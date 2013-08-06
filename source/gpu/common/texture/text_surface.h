#ifndef _H_PUNK_TEXT_TEXTURE
#define _H_PUNK_TEXT_TEXTURE

#include "../../../config.h"
#include "../../../string/string.h"
#include <cstddef>

namespace System
{
    class Buffer;
}

namespace Gpu
{
    class Texture2D;
    class VideoDriver;

    class PUNK_ENGINE_API TextSurface final
    {
    public:
        enum TextHorizontalAlignment { HORIZONTAL_LEFT, HORIZONTAL_RIGHT, HORIZONTAL_CENTER, HORIZONTAL_WIDTH };
        enum TextVerticalAlignment { VERTICAL_TOP, VERTICAL_BOTTOM, VERTICAL_CENTER };
        enum TextDirection { DIRECTION_HORIZONTAL, DIRECTION_VERTICAL };

        TextSurface(VideoDriver* driver);
        TextSurface(size_t width, size_t height, VideoDriver* driver);
        virtual ~TextSurface();

        void SetSize(int width, int height);
        void SetAutoWrapFlag(bool value) { m_auto_wrap = value; }
        bool GetAutoWrapFlag() const { return m_auto_wrap; }
        void SetAutoFitSizeFlag(bool value) { m_auto_fit_size = value; }
        bool GetAutoFitSizeFlag() const { return m_auto_fit_size; }
        void SetText(const System::string& text);
        const System::string& GetText() const;
        Texture2D* GetTexture();

        virtual void Save(System::Buffer* buffer) const;
        virtual void Load(System::Buffer* buffer);

        void SetFont(const System::string& font);
        const System::string& GetFont() const { return m_font; }

        void SetTextSize(int size);
        int GetTextSize() const { return m_font_size; }

        void SetHorizontalAlignment(TextHorizontalAlignment value) { m_halignment = value; RenderTextToTexture(); }
        TextHorizontalAlignment GetHorizontalAlignment() const { return m_halignment; }

        void SetVerticalAlignment(TextVerticalAlignment value) { m_valignment = value; RenderTextToTexture(); }
        TextVerticalAlignment GetVerticalAlignment() const { return m_valignment; }

    private:
        int CalculateTextXOffset(const System::string& text);
        int CalculateTextYOffset(const System::string& text);
        bool RenderTextToTexture();
        void UpdateTextureSize();

    private:
        TextHorizontalAlignment m_halignment;
        TextVerticalAlignment m_valignment;
        bool m_auto_wrap;
        bool m_auto_fit_size;
        bool m_need_update;
        int m_font_size;
        System::string m_text;
        System::string m_font;

        //	should be destroyed in destructor
        Texture2D* m_texture;
        VideoDriver* m_video_driver;
    };
}

#endif	//	_H_PUNK_TEXT_TEXTURE
