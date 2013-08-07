#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32

#ifdef __gnu_linux__
#include "../gl/module.h"
#endif
#include <map>
#include <list>

#include "video_memory.h"
#include "../../common/video_driver.h"
#include "../../common/video_driver_caps.h"
#include "../render_targets/module.h"

namespace Gpu
{
    class FrameBufferConfig;
    class Texture2DArray;

    namespace OpenGL
    {
        class PUNK_ENGINE_LOCAL VideoDriverImpl : public VideoDriver
        {
        public:
            //	constructoion part
            VideoDriverImpl(const VideoDriverDesc& desc);
            virtual ~VideoDriverImpl();
            virtual Utility::FontBuilder* GetFontBuilder() override;
            virtual void SetFullScreen(bool flag) override;
            virtual System::Window* GetWindow() override;
            virtual Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) override;
            virtual Texture2DArray* CreateTexture2DArray(int width, int height, int depth, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) override;
            virtual FrameBuffer* CreateFrameBuffer(FrameBufferConfig* config) override;
            virtual void SetViewport(float x, float y, float width, float height) override;
            virtual void SetClearColor(const Math::vec4& color) override;
            virtual void SetClearDepth(float value) override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual void SwapBuffers() override;
            virtual const Config& GetConfig() const override;
            virtual size_t GetFrameBufferConfigCount() const override;
            virtual FrameBufferConfig* GetFrameBufferConfig(size_t index) override;
            virtual FrameBuffer* CreateFrameBuffer() override;
            virtual const VideoDriverCaps& GetCaps() override;

            bool IsExtensionSupported(const char *extList, const char *extension);
            void InitExtensions();

#ifdef __gnu_linux__
            void InitGlxFunctions();
            GLXFBConfig* ChooseConfis(Display* display, Window window);
            int* GetVisualAttributes();
            int* GetContextAttributes();
            int GetGlxMinorVersion();
            int GetGlxMajorVersion();
            void BindWindow(System::Window* window);
            void SelectVisualInfo();
            void CreateOpenGLContext();
            void CreateOpenGLWindow();
            void StartLinuxDriver();
            void ShutdownLinuxDriver();
#endif

            OpenGL::VideoMemory* GetVideoMemory();
            const OpenGL::VideoMemory* GetVideoMemory() const;

            Display* GetDisplay();

        private:

            int m_shader_version;
            int m_opengl_version;

#ifdef __gnu_linux__
            int m_glx_version;
#endif

#ifdef _WIN32
            HGLRC m_opengl_context;
#elif defined __gnu_linux__
            __GLXcontextRec* ctx;
            Display* m_display;
            Window m_window;
            GLXFBConfig m_best_fbc;
            XVisualInfo* m_visual_info;
            int m_glx_minor_version;
            int m_glx_major_version;
            XF86VidModeModeInfo m_default_mode;
#endif

            VideoDriverDesc m_desc;            
            OpenGL::VideoMemory* m_memory;            
            std::vector<FrameBufferConfig> m_fb_config;
            std::vector<OpenGL::OpenGLFrameBuffer*> m_frame_buffer;
            VideoDriverCaps m_caps;

        private:
            void Init();
            void Clear();
            void ReadConfig();
            void InitShaderPrograms();
            void SubscribeForSystemMessages();
            void InitInternalVertexBuffers();
        };
    }
}

#endif	//	_H_PUNK_OPENGL_DRIVER_WIN32
