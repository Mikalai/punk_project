#ifndef _H_PUNK_OPENGL_SCALED_GRID
#define _H_PUNK_OPENGL_SCALED_GRID

#include "../renderable.h"

namespace GPU
{
    class VideoDriver;

    class PUNK_ENGINE_API ScaledGridObject : public Renderable
	{
	public:
        ScaledGridObject(VideoDriver* driver);
        virtual ~ScaledGridObject();
        virtual void Bind(int64_t) override;
        virtual void Unbind() override;
        virtual void Render() override;

        void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels);
		float GetTotalWidth() const;
		float GetTotalHeight() const;

	private:
		ScaledGridObject(const ScaledGridObject& quad) = delete;
		ScaledGridObject& operator = (const ScaledGridObject& quad) = delete;

        class ScaledGridObjectImpl;
        ScaledGridObjectImpl* impl;
	};
}

#endif	//	_H_PUNK_OPENGL_SCALED_GRID
