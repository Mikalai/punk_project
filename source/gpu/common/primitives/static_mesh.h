#ifndef _H_PUNK_OPENGL_MODULE_STATIC_OBJECT
#define _H_PUNK_OPENGL_MODULE_STATIC_OBJECT

#include "../renderable.h"

namespace Virtual { class StaticGeometry; }

namespace GPU
{
    class VideoDriver;

    class PUNK_ENGINE_API StaticMesh : public Renderable
	{
	public:

		StaticMesh(VideoDriver* driver);
        virtual ~StaticMesh();
        virtual void Bind(int64_t value) override;
        virtual void Unbind() override;
        virtual void Render() override;
        bool Cook(Virtual::StaticGeometry* desc);
        bool HasData();

    private:
        StaticMesh(const StaticMesh&) = delete;
        StaticMesh& operator = (const StaticMesh&) = delete;

        class StaticMeshImpl;
        StaticMeshImpl* impl;
	};
}

#endif
