/*
File: Driver.cpp
Author: Abramau Mikalaj
Description: Contains implementation, for now not the best, of initialization
and deinitialization rutines
*/

#ifdef __linux__

#include "../driver.h"
#include "../../../../system/window.h"
#include "../../../../common/logger.h"
#include "../../../../images/bmp/bmp.h"
#include "../glsl_program.h"
#include "../extensions.h"

namespace CommonStaff
{
    ::Driver::Video::Driver g_openGLDriver;
}

namespace Driver
{
    namespace Video
    {
        namespace OpenGL
        {
            int Driver::ShaderVersion = 0;
            int Driver::OpenGLVersion = 0;

            DriverParameters Driver::m_parameters;

            Driver::Driver()
            {}

            bool Driver::Init(const DriverParameters* parameters)
            {
                printf("Inititalizing\n");
                System::Logger::GetInstance()->WriteMessage("[Video] Starting video engine");
                m_parameters = *parameters;
                printf("Init opengl\n");
                if (!InitOpenGL())
                {
                    System::Logger::GetInstance()->WriteError("[Video] OpenGL failed to initialize");
                    LOG_LOCATION;
                    return false;
                }
                printf("Init view\n");
                if (!InitView())
                {
                    printf("Init not ok\n");
                    System::Logger::GetInstance()->WriteError("[Video] Unable to initialize view");
                    LOG_LOCATION;
                    return false;
                }
                printf("Init of\n");
                return true;
            }

            bool Driver::InitView()
            {
                printf("glViewport address is %p\n", glViewport);
                glViewport(0, 0, 800, 600);//m_parameters.width, m_parameters.height);
                return true;
            }

            bool Driver::OnResize()
            {
                if (!m_parameters.fullScreen)
                {
                    //RECT rect;
                    //GetClientRect(m_parameters.window, &rect);
                    //m_parameters.width = rect.right - rect.left;
                    //m_parameters.height = rect.bottom - rect.top;
                }
                return InitView();
            }

            bool Driver::InitOpenGL()
            {
                InitExtensions(0);

                GLenum err = glGetError();

                glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
                CheckError();
                glEnable(GL_DEPTH_TEST);

                CheckError();

                GLint t;
                System::Logger::GetInstance()->WriteMessage("[Video] Renderer: %s (In %s line %d in %s)", glGetString(GL_RENDERER), __FILE__, __LINE__, __FUNCTION__);
                System::Logger::GetInstance()->WriteMessage("[Video] Vendor: %s", glGetString(GL_VENDOR));
                System::Logger::GetInstance()->WriteMessage("[Video] Version: %s", glGetString(GL_VERSION));
                System::Logger::GetInstance()->WriteMessage("[Video] GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

                const unsigned char* sv= glGetString(GL_SHADING_LANGUAGE_VERSION);
                ShaderVersion = ((int)(sv[0]-'0'))*100;
                ShaderVersion += ((int)(sv[2]-'0'))*10;
                ShaderVersion += ((int)(sv[3]-'0'));

                sv = glGetString(GL_VERSION);
                OpenGLVersion = ((int)(sv[0]-'0'))*100;
                OpenGLVersion += ((int)(sv[2]-'0'))*10;
                OpenGLVersion += ((int)(sv[3]-'0'));

                glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
                System::Logger::GetInstance()->WriteMessage("[Video] Max vertex attribs: %d", t);
                glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
                System::Logger::GetInstance()->WriteMessage("[Video] Max vertex uniform components: %d", t);
                glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
                System::Logger::GetInstance()->WriteMessage("[Video] Max varying floats: %d", t);

                int profile;
                glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
                if (profile & GLX_CONTEXT_CORE_PROFILE_BIT_ARB)
                    System::Logger::GetInstance()->WriteMessage("[Video] Core profile selected");
                if (profile & GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
                    System::Logger::GetInstance()->WriteMessage("[Video] Compatible profile selected");
                GLSLProgram::Init();
                return true;
            }

            bool Driver::MakeFullScreen(bool full)
            {
                m_parameters.fullScreen = full;
                return Reboot();
            }

            bool Driver::Reboot(const DriverParameters* params)
            {
                /*	if (params)
                                m_parameters = *params;

                        if (!m_parameters.fullScreen)
                        {
                                ChangeDisplaySettings(NULL, 0);
                                ShowCursor(TRUE);
                                MoveWindow(m_parameters.window, 100, 100, m_parameters.width, m_parameters.height, TRUE);
                        }
                        else
                        {
                                DEVMODE mode;
                                ZeroMemory(&mode, sizeof(mode));
                                mode.dmSize = sizeof(mode);
                                mode.dmPelsWidth = m_parameters.width;
                                mode.dmPelsHeight = m_parameters.height;
                                mode.dmBitsPerPel = m_parameters.bitsPerPixel;
                                mode.dmDisplayFrequency = m_parameters.refreshRate;
                                mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

                                MoveWindow(m_parameters.window, 0, 0, m_parameters.width, m_parameters.height, TRUE);

                                if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
                                        return false;

                                ShowCursor(FALSE);
                        }


                        if (m_parameters.fullScreen)
                        {
                                SetWindowLong(m_parameters.window, GWL_STYLE, WS_POPUP);
                                SetWindowLong(m_parameters.window, GWL_EXSTYLE, WS_EX_APPWINDOW);
                        }
                        else
                        {
                                SetWindowLong(m_parameters.window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                                SetWindowLong(m_parameters.window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
                        }

                        ShowWindow(m_parameters.window, SW_SHOW);
                        UpdateWindow(m_parameters.window);

                        return true;*/
            }


            Driver::~Driver()
            {
                /*	ChangeDisplaySettings(NULL, 0);
                        wglMakeCurrent(m_parameters.deviceContext,NULL);
                        wglDeleteContext(m_parameters.openglContext);
                        ReleaseDC(m_parameters.window, m_parameters.deviceContext);*/
            }

            bool Driver::MakeScreenShot()
            {
                FILE *f = 0;
                f = fopen("screenshot.bmp", "wb");
                if (f == 0)
                    return false;
                try
                {
                    GLubyte* data = 0;
                    GLenum type = 0;
                    if (m_parameters.bitsPerPixel == 8)
                    {
                        type = GL_UNSIGNED_BYTE_2_3_3_REV;
                        data = new GLubyte[m_parameters.width*m_parameters.height];
                        memset(data, 0, m_parameters.width*m_parameters.height);
                    }
                    else if (m_parameters.bitsPerPixel == 16)
                    {
                        type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
                        data = new GLubyte[m_parameters.width*m_parameters.height*2];
                        memset(data, 0, m_parameters.width*m_parameters.height*2);
                    }
                    else if (m_parameters.bitsPerPixel == 32)
                    {
                        type = GL_UNSIGNED_INT_8_8_8_8_REV;
                        data = new GLubyte[m_parameters.width*m_parameters.height*4];
                        memset(data, 0, m_parameters.width*m_parameters.height*4);
                    }
                    else
                        return false;

                    try
                    {
                        glReadPixels(0, 0, m_parameters.width, m_parameters.height, GL_RGBA, type, data);

                        BITMAP_FILEHEADER fileHeader;
                        memset(&fileHeader, 0, sizeof(fileHeader));
                        fileHeader.Signature= 19778;
                        fileHeader.Reserved = 0;
                        fileHeader.Size = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER)+m_parameters.width*m_parameters.height*3;
                        fileHeader.BitsOffset = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER);
                        BITMAP_HEADER infoHeader;
                        memset(&infoHeader, 0, sizeof(infoHeader));
                        infoHeader.SizeImage = sizeof(infoHeader);
                        infoHeader.Width = m_parameters.width;
                        infoHeader.Height = m_parameters.height;
                        infoHeader.Planes = 1;
                        switch (type)
                        {
                        case GL_UNSIGNED_BYTE_2_3_3_REV:
                            infoHeader.BitCount = 8;
                            break;
                        case GL_UNSIGNED_SHORT_4_4_4_4_REV:
                            infoHeader.BitCount = 16;
                            break;
                        case GL_UNSIGNED_INT_8_8_8_8_REV:
                            infoHeader.BitCount = 24;
                            break;
                        default:
                            return false;
                        }
                        infoHeader.Compression = 0;
                        fwrite(&fileHeader, sizeof(fileHeader), 1, f);
                        fwrite(&infoHeader, sizeof(infoHeader), 1, f);
                        if (type == GL_UNSIGNED_INT_8_8_8_8_REV)
                        {
                            for (unsigned i = 0; i < m_parameters.width*m_parameters.height; i++)
                            {
                                fwrite(data + i*4 + 2, sizeof(data[0]), 1, f);
                                fwrite(data + i*4 + 1, sizeof(data[0]), 1, f);
                                fwrite(data + i*4, sizeof(data[0]), 1, f);
                            }
                        }
                        else if (type == GL_UNSIGNED_SHORT_4_4_4_4_REV)
                        {
                            throw System::SystemError("I don't know how to export 4 bits per red \
                                                    4 bits per green 4 bits per blue and 4 bits per alpha surface \
                                                    into bitmap with 16 bits per pixel");
                        }
                        else if (type == GL_UNSIGNED_BYTE_2_3_3_REV)
                        {
                            throw System::SystemError("Oh, the same shit like with 16 bits");
                        }

                        delete[] data;
                    }
                    catch (...)
                    {
                        delete[] data;
                        throw;
                    }
                    fclose(f);
                }
                catch (...)
                {
                    fclose(f);
                    throw;
                }
                return true;
            }

            bool Driver::SwapBuffers()
            {
                glXSwapBuffers(m_parameters.display, m_parameters.window);
                return true;
            }

            bool Driver::IsExtensionSupported(const char* ext)
            {
                std::string where = std::string((char*)glGetString(GL_EXTENSIONS));
                std::string what = std::string(ext);
                if (where.find(ext, 0) == std::string::npos)
                    return false;
                else
                    return true;
            }

            const DriverParameters* Driver::GetParameters() const
            {
                return &m_parameters;
            }

        }
    }
}

#endif
