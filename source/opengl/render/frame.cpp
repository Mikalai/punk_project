#include "frame.h"
#include "render_pass.h"
#include "../win32/driver_win32.h"
#include "../../system/logger.h"

namespace OpenGL
{
	void Frame::Begin()
	{
		m_profiler.Start(L"Render frame");				
	}

	void Frame::End()
	{
		for (auto it = m_render_passes.begin(); it != m_render_passes.end(); ++it)
		{
			RenderPass* pass = *it;
			pass->Render();
		}

		Clear();
		m_profiler.End();
		Driver::Instance()->SwapBuffers();
		out_message() << m_profiler.ToString() << std::endl;
	}

	void Frame::AddRenderPass(RenderPass* pass)
	{
		m_render_passes.push_back(pass);
	}

	void Frame::Clear()
	{
		for (auto it = m_render_passes.begin(); it != m_render_passes.end(); ++it)
		{
			delete *it;
		}
		m_render_passes.clear();
	}
}
