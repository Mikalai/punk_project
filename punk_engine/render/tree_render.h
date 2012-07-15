#ifndef _H_TREE_RENDER
#define _H_TREE_RENDER

#include "config.h"
#include "../system/driver/video/driver.h"
#include "../system/system.h"

namespace Render
{
	class LIB_RENDER TreeRender
	{
	public:
		typedef System::Resource<OpenGL::StaticObject> VAO;
		typedef System::Resource<OpenGL::Texture2D> Texture;
		typedef OpenGL::RenderContextLight RenderContext;
	private:
		VAO* m_trunk;
		VAO* m_top_leaves;
		VAO* m_bottom_leaves;
		Texture* m_trunk_texture;
		Texture* m_leaves_texture;
		std::auto_ptr<RenderContext> m_rc;
	public:
		void Init(VAO* trunk, VAO* top_leaves, VAO* bottom);
		RenderContext& GetRenderContext();
		void Render();
	};
}

#endif