#ifndef _H_PUNK_RENDER_PIEPLINE
#define _H_PUNK_RENDER_PIEPLINE

#include <vector>
#include "renderable.h"

namespace Render
{
    class RenderPipeline 
    {
    public:
		virtual void Process() = 0;
		virtual void AddStaticRenderable(StaticRenderable r) = 0;
		virtual void SetViewMatrix(const Math::mat4& m) = 0;
		virtual void SetProjectionMatrix(const Math::mat4& m) = 0;
    };
}

#endif