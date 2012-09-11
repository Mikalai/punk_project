#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT
#define _H_PUNK_OPENGL_RENDER_CONTEXT

#include "../../config.h"
#include <map>
#include <list>
#include "../render_context/dummy_render_context_policy.h"
#include "batch.h"

namespace OpenGL
{
	class RenderTarget;
	class PUNK_ENGINE RenderPass
	{
		std::map<TextureContext*, std::map<DummyRenderPolicy*, std::list<Batch*> > > m_batches;
		RenderTarget* m_render_target;
		//
		//	TODO: Add render target
		//
	public:
		RenderPass();
		~RenderPass();
		virtual void Render();
		void SetRenderTarget(RenderTarget* target) { m_render_target = target; }
		RenderTarget* GetRenderTarget() { return m_render_target; }
		const RenderTarget* GetRenderTarget() const { return m_render_target; }
		void AddBatch(TextureContext* textures, DummyRenderPolicy* context, Batch* batch);
	};
}

#endif