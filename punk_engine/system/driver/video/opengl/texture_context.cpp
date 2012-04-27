#include "texture_context.h"
#include "texture_context_impl.h"

namespace OpenGL
{
	TextureContext::TextureContext() 
		: impl_tc(new TextureContextImpl())
	{}

	TextureContext::TextureContext(const TextureContext& tc)
		: impl_tc(new TextureContextImpl(*tc.impl_tc))
	{}

	TextureContext& TextureContext::operator= (const TextureContext& tc)
	{
		TextureContext temp(tc);
		std::swap(impl_tc, temp.impl_tc);
		return *this;
	}

	TextureContext::~TextureContext()
	{
		impl_tc.reset(0);
	}

	void TextureContext::Bind()
	{
		impl_tc->Bind();
	}
	
	void TextureContext::Unbind()
	{
		impl_tc->Unbind();
	}

	void TextureContext::SetTexture0(const Texture2D* map)
	{
		impl_tc->m_diffuse_map = map;
	}

	void TextureContext::SetTexture1(const Texture2D* map)
	{
		impl_tc->m_normal_map = map;
	}
}