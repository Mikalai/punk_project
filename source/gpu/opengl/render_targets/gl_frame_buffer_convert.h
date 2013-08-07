#ifndef GL_FRAME_BUFFER_CONVERT_H
#define GL_FRAME_BUFFER_CONVERT_H

#include "../gl/module.h"
#include "../../common/frame_buffer/frame_buffer_target.h"

namespace Gpu
{
    namespace OpenGL
    {
        GLenum Convert(const FrameBufferTarget& target);
    }
}

#endif // GL_FRAME_BUFFER_CONVERT_H
