#include "text_surface.h"
#include "video_driver.h"
#include "texture2d.h"
#include "../../utility/fonts/font_builder.h"

namespace GPU
{
    TextSurface::TextSurface(VideoDriver *driver)
        : m_video_driver(driver)
    {}

    TextSurface::TextSurface(size_t width, size_t height, VideoDriver *driver)
        : m_video_driver(driver)
        , m_need_update(false)
    {
        m_texture = m_video_driver->CreateTexture2D(width, height, ImageModule::IMAGE_FORMAT_RED, nullptr, false);
        m_halignment = TextHorizontalAlignment::HORIZONTAL_LEFT;
        m_valignment = TextVerticalAlignment::VERTICAL_TOP;
        m_font = L"times.ttf";
        m_font_size = 14;
        m_auto_wrap = false;
    }

    TextSurface::~TextSurface()
    {
        safe_delete(m_texture);
    }

    void TextSurface::SetSize(int width, int height)
    {
        if (!m_texture)
            m_texture = m_video_driver->CreateTexture2D(width, height, ImageModule::IMAGE_FORMAT_ALPHA, 0, false);
        else
            m_texture->Resize(width, height);
    }

    int TextSurface::CalculateTextXOffset(const System::string& text)
    {
        int start_x;
        if (TextHorizontalAlignment::HORIZONTAL_LEFT == m_halignment)
            start_x = 0;
        else if (TextHorizontalAlignment::HORIZONTAL_CENTER == m_halignment)
        {
			int length = m_video_driver->GetFontBuilder()->CalculateLength(text.Data());
            if (length >= m_texture->GetWidth())
                start_x = 0;
            else
                start_x = (m_texture->GetWidth() - length) / 2;
        }
        else if (TextHorizontalAlignment::HORIZONTAL_RIGHT == m_halignment)
        {
			int length = m_video_driver->GetFontBuilder()->CalculateLength(text.Data());
            if (length >= m_texture->GetWidth())
                start_x = 0;
            else
                start_x = m_texture->GetWidth() - length;
        }
        return start_x;
    }

    int TextSurface::CalculateTextYOffset(const System::string& text)
    {
        const char* cur = text.Data();
		int length = m_video_driver->GetFontBuilder()->CalculateLength(cur);
        if (length == 0)
            return 1;
		int max_offset = m_video_driver->GetFontBuilder()->GetMaxOffset(text);
		int min_offset = m_video_driver->GetFontBuilder()->GetMinOffset(text);
        int max_height = max_offset - min_offset;
        //int max_lines = m_texture->GetHeight() / max_height;
        int req_lines = length / m_texture->GetWidth();
        int start_y = 0;
        if (TextVerticalAlignment::VERTICAL_BOTTOM == m_valignment)
        {
            start_y = 0;
        }
        else if (TextVerticalAlignment::VERTICAL_CENTER == m_valignment)
        {
            start_y = m_texture->GetHeight() / 2 + req_lines*max_height / 2;
        }
        else if (TextVerticalAlignment::VERTICAL_TOP == m_valignment)
        {
            start_y = max_offset;
        }
        return start_y;
    }

    bool TextSurface::RenderTextToTexture()
    {
        UpdateTextureSize();

        if (!m_texture)
            return false;

        m_texture->Fill(0);

        if (m_text.Length() == 0)
            if (m_texture)
                return true;

		m_video_driver->GetFontBuilder()->SetCurrentFace(m_font);
		m_video_driver->GetFontBuilder()->SetCharSize(m_font_size, m_font_size);

        int start_x, start_y;
        int x = start_x = CalculateTextXOffset(m_text);
        int y = start_y = CalculateTextYOffset(m_text);

        for (const char* a = m_text.Data(); *a; a++)
        {
            int width;
            int height;
            int x_offset;
            int y_offset;
            int x_advance;
            int y_advance;
            unsigned char* buffer;
			m_video_driver->GetFontBuilder()->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
            if (x_offset < 0 && x == 0)
                x += -x_offset;
            if (x + x_offset + width >= m_texture->GetWidth())
            {
				y -= m_video_driver->GetFontBuilder()->GetHeight(L'M');
                x = CalculateTextXOffset(a);
                if (y < 0)
                    return true;
            }
            m_texture->CopyFromCpu(x + x_offset, y - y_offset, width, height, buffer);
            x += x_advance;
        }
        return true;
    }

    void TextSurface::SetFont(const System::string& font)
    {
        m_font = font;
        m_need_update = true;
    }

    void TextSurface::SetTextSize(int size)
    {
        m_font_size = size;
        m_need_update = true;
    }

    void TextSurface::SetText(const System::string& text)
    {
        m_text = text;
        m_need_update = true;
    }


    bool TextSurface::Save(std::ostream&) const
    {
        return true;
    }

    bool TextSurface::Load(std::istream&)
    {
        return true;
    }

    void TextSurface::UpdateTextureSize()
    {
        if (GetAutoFitSizeFlag())
        {
			auto width = m_video_driver->GetFontBuilder()->CalculateLength(m_text);
            auto height = m_video_driver->GetFontBuilder()->CalculateHeight(m_text);
            m_texture->Resize(width, height);
        }
    }
}
