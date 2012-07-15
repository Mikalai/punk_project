#ifndef _H_PUNK_SIMPLE_PIPELINE
#define _H_PUNK_SIMPLE_PIPELINE

#include "pipeline.h"
#include "config.h"

namespace OpenGL
{
	class RenderContextSkinning;
	class RenderContextLight;
	class RenderContextBumpMapping;
	class TextureContext;
}

namespace Render
{
	class LIB_RENDER SimpleRender : public RenderPipeline
	{
		//std::auto_ptr<GUI::Manager> m_gui;
		//OpenGL::Driver m_driver;
		Math::mat4 m_view_matrix;
		Math::mat4 m_proj_matrix;
		//std::auto_ptr<OpenGL::RenderContextSkinning> m_skinning_context;
		std::auto_ptr<OpenGL::RenderContextBumpMapping> m_bump_mapping;
		std::auto_ptr<OpenGL::TextureContext> m_texture_context;		
		std::vector<StaticRenderable> m_queue;
	public:
		SimpleRender();
		virtual void Process();
		virtual void AddStaticRenderable(StaticRenderable r);	
		virtual void SetViewMatrix(const Math::mat4& m);
		virtual void SetProjectionMatrix(const Math::mat4& m);

	};
}

#endif