#ifndef FRAME_BUFFER_TARGET_H
#define FRAME_BUFFER_TARGET_H

namespace Gpu
{
    enum class FrameBufferTarget {
        TargetNone,
        TargetFrontLeft,
        TargetFrontRight,
        TargetBackLeft,
        TargetBackRight,
        TargetFront,
        TargetBack,
        TargetLeft,
        TargetRight,
        TargetFrontBack
    };
}

#endif // FRAME_BUFFER_TARGET_H
