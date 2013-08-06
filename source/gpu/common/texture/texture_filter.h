#ifndef TEXTURE_FILTER_H
#define TEXTURE_FILTER_H

namespace Gpu
{
    enum class TextureFilter { Nearest,
                               Linear,
                               NearestMipmapNearest,
                               LinearMipmapNearest,
                               NearestMipmapLinear,
                               LinearMipmapLinear
                             };
}

#endif // TEXTURE_FILTER_H
