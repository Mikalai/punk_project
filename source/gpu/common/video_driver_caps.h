#ifndef VIDEO_DRIVER_CAPS_H
#define VIDEO_DRIVER_CAPS_H

namespace Gpu
{
    struct VideoDriverCaps
    {
        bool IsMultisamplingEnabled;
        bool IsCoverageSamplingEnabled;
        size_t ShadowMapSize;
    };
}

#endif // VIDEO_DRIVER_CAPS_H
