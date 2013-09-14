#ifndef GL_CAPABILITIES_H
#define GL_CAPABILITIES_H

#include <vector>
#include "../../common/frame_buffer/frame_buffer_config.h"
#include "../../common/frame_buffer/render_buffer_config.h"
namespace Gpu
{
    namespace OpenGL
    {
        class VideoDriverImpl;

        bool IsMultisamplingSupported(VideoDriverImpl* driver);
        bool IsCoverageSamplingSupported(VideoDriverImpl* driver);
        bool IsShaderIncludeSupported(VideoDriverImpl* driver);
        int GetMaxMultisampleDepth(VideoDriverImpl* driver);
        int GetCoverageSampleConfigsCount(VideoDriverImpl* driver);
        void GetCoverageConfigs(std::vector<int>& value, VideoDriverImpl* driver);
        void GetFrameBufferConfigs(std::vector<FrameBufferConfig>& value, VideoDriverImpl* driver);
        void GetColorBufferConfigs(std::vector<RenderBufferConfig>& value, VideoDriverImpl* driver);
        void GetDepthBufferConfigs(std::vector<RenderBufferConfig>& value, VideoDriverImpl* driver);
    }
};

#endif // GL_CAPABILITIES_H
