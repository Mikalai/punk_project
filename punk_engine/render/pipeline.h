#ifndef _H_PUNK_RENDER_PIEPLINE
#define _H_PUNK_RENDER_PIEPLINE

#include "../system/allocator.h"
//#include "render_element.h"
#include "font_builder.h"
#include <vector>

namespace Render
{
	class AbstractRender;

    class RenderPipeline //: public SimpleContainer<RenderElement*>
    {
		struct Item
		{
			AbstractRender* m_render;
			void* m_parameters;
			Item(AbstractRender* render, void *parameters) : m_render(render), m_parameters(parameters) {}
		};

		std::vector<Item> m_queue;

    public:

		static RenderPipeline* GetRenderPipeline();

        RenderPipeline();
        ~RenderPipeline();
		void Process();
		void Add(AbstractRender* render, void* parameters);

    };

}

#endif