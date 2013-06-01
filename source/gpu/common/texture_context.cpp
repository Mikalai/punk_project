#include "texture_context.h"
#include "texture2d.h"

namespace GPU
{

TextureContext::TextureContext()
{
    memset(m_textures, 0, sizeof(m_textures));
}

TextureContext::~TextureContext()
{

}

void TextureContext::Clear()
{
    memset(m_textures, 0, sizeof(m_textures));
}

void TextureContext::Bind()
{
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        if (m_textures[i])
        {
            m_textures[i]->Bind(i);
        }
    }
}

void TextureContext::Unbind()
{
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        if (m_textures[i])
        {
            m_textures[i]->Unbind();
            m_textures[i] = nullptr;
        }
    }
}

void TextureContext::SetTexture(int slot, const Texture2D* map)
{
    m_textures[slot] = map;
}

}
