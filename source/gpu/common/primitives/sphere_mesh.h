#ifndef _H_PUNK_SPHERE_MESH
#define _H_PUNK_SPHERE_MESH

#include "../renderable.h"

namespace GPU
{
    class VideoDriver;

    class PUNK_ENGINE_API SphereObject : public Renderable
	{
	public:
		SphereObject(VideoDriver* driver);
        virtual ~SphereObject();
		void Cook(float radius);
        virtual void Bind(int64_t value) override;
        virtual void Unbind() override;
        virtual void Render() override;

    private:
        class SphereObjectImpl;
        SphereObjectImpl* impl;
	};
}

#endif	//	_H_PUNK_SPHERE_MESH
