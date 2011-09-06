#include "pipeline.h"
#include "render.h"

namespace Render
{
	RenderPipeline* g_pipeline;

	RenderPipeline* RenderPipeline::GetRenderPipeline()
	{
		if (g_pipeline)
			return g_pipeline;
		g_pipeline = new RenderPipeline();
		return g_pipeline;
	}

	RenderPipeline::RenderPipeline()
	{

	}

	RenderPipeline::~RenderPipeline()
	{
	}

	void RenderPipeline::Add(AbstractRender* render, void* parameters)
	{
		m_queue.push_back(Item(render, parameters));
	}

	void RenderPipeline::Process()
	{
		for (std::vector<Item>::iterator it = m_queue.begin(); it != m_queue.end(); ++it)
		{
			(*it).m_render->Render((*it).m_parameters);
			//At(i)->BindShaderData();			
		}
		m_queue.clear();
	}
}