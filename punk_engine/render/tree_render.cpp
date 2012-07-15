#include "tree_render.h"

namespace Render
{
	void TreeRender::Init(VAO* trunk, VAO* top_leaves, VAO* bottom)
	{
		m_trunk = trunk;
		m_top_leaves = top_leaves;
		m_bottom_leaves = bottom;

		m_rc.reset(new RenderContext);
	}

	TreeRender::RenderContext& TreeRender::GetRenderContext()
	{
		return *m_rc;
	}

	void TreeRender::Render()
	{

	}
}
