#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "../../../config.h"
#include "../../../system/poolable.h"

#include <memory>

namespace Gpu
{
class Texture2D;


class PUNK_ENGINE_API TextureContext : public System::Poolable<TextureContext>
{
public:
    TextureContext();
    ~TextureContext();

    void SetTexture(int slot, Texture2D* map);
    void Clear();

    void Bind();
    void Unbind();
private:
    static const int MAX_TEXTURES = 32;
    //	this pointers should not be deleted in destructor
    Texture2D* m_textures[MAX_TEXTURES];
private:
    TextureContext(const TextureContext& tc);
    TextureContext& operator = (const TextureContext& tc);
};

}

#endif
