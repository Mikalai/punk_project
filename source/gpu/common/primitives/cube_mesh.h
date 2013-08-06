#ifndef _H_PUNK_OPENGL_CUBE_MESH
#define _H_PUNK_OPENGL_CUBE_MESH

#include "../renderable.h"

namespace Gpu
{
    class VideoDriver;
    class PUNK_ENGINE_API CubeObject : public Renderable
	{		
	public:
        CubeObject(VideoDriver* driver);
        virtual ~CubeObject();

		void Cook(float width, float height, float depth);

        virtual void Bind(int64_t) override;
        virtual void Unbind() override;
        virtual void Render() override;

    private:
        CubeObject(const CubeObject&) = delete;
        CubeObject& operator = (const CubeObject&) = delete;

    private:
        class CubeObjectImpl;
        CubeObjectImpl* impl;
	};
}

#endif	//	_H_PUNK_OPENGL_CUBE_MESH
