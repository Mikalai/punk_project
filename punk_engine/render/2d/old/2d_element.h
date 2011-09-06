#ifndef _H_PUNK_2D_ELEMENT
#define _H_PUNK_2D_ELEMENT

#include "..\render.h"

namespace Render
{
	namespace _2D
	{
		class _2DRender : public ::Render::AbstractRender
		{
			_2DRenderElement(const _2DRenderElement&);
			_2DRenderElement& operator = (const _2DRenderElement&);
		protected:
			
			Math::mat4 worldViewProj;

		public:
			_2DRenderElement();
			_2DRenderElement(int x, int y, int width, int height);
		
		};
	}
}

#endif