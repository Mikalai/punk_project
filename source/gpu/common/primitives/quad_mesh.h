#ifndef _H_PUNK_OPENGL_QUAD
#define _H_PUNK_OPENGL_QUAD

#include "../renderable.h"

namespace Gpu
{
    class VideoDriver;

    class PUNK_ENGINE_API QuadObject final : public Renderable
	{
	public:
		QuadObject(VideoDriver* driver);
        virtual ~QuadObject();

		void Cook(float width, float height);
        virtual void Bind(int64_t) override;
        virtual void Unbind() override;
        virtual void Render() override;

    private:
        QuadObject(const QuadObject&) = delete;
        QuadObject& operator = (const QuadObject&) = delete;

        class QuadObjectImpl;
        QuadObjectImpl* impl;
	};
}

#endif
