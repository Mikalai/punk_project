#ifndef _H_PUNK_OPENGL_MODULE_GRID_OBJECT
#define _H_PUNK_OPENGL_MODULE_GRID_OBJECT

#include "../renderable.h"

namespace GPU
{
    class VideoDriver;

    class PUNK_ENGINE_API GridObject : public Renderable
	{		
	public:

        GridObject(VideoDriver* driver);
        virtual ~GridObject();

        void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices);

        virtual void Bind(int64_t) override;
        virtual void Unbind() override;
        virtual void Render() override;

	private:
		GridObject(const GridObject& quad) = delete;
		GridObject& operator = (const GridObject& quad) = delete;

        class GridObjectImpl;
        GridObjectImpl* impl;
	};
}
#endif
