#include "module.h"
#include "opengl/module.h"

namespace Gpu
{
    VideoDriver* Init(const VideoDriverDesc& data)
	{
        OpenGL::VideoDriverImpl* driver = new OpenGL::VideoDriverImpl(data);
        OpenGL::InitOpenGL(driver);
        return driver;
	}

    void Destroy(VideoDriver *driver)
	{		
		Frame::ClearPool();
		TextureContext::ClearPool();
		CoreState::ClearPool();
        OpenGL::DestroyOpenGL();
        delete driver;
	}
}
