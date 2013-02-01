#include "render_target.h"
#include "../error/module.h"

namespace GPU
{
	RenderTarget::Properties::Properties()
		: m_type(RENDER_TARGET_NONE)
		, m_clear_mask(COLOR_BUFFER|DEPTH_BUFFER|STENCIL_BUFFER)
		, m_r(0.8f)
		, m_g(0.8f)
		, m_b(0.8f)
		, m_a(1.0f)
	{}

	void RenderTarget::SetClearColor(float r, float g, float b, float a)
	{
		m_r = r; m_g = g; m_b = b; m_a = a;
	}

	void RenderTarget::SetClearMask(int mask)
	{
		m_clear_mask = mask;
	}

	bool RenderTarget::Init(RenderTarget::Properties* props)
	{
		throw GPUNotImplementedException();
	}

	void RenderTarget::Activate()
	{
		throw GPUNotImplementedException();
	}

	void RenderTarget::Deactivate()
	{
		throw GPUNotImplementedException();
	}

	RenderTarget::~RenderTarget()
	{}
}
