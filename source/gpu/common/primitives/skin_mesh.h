#ifndef _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
#define _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT

#include "../renderable.h"

namespace Virtual { class SkinGeometry; }
namespace Virtual { class Armature; }

namespace Math { class vec4; }

namespace Gpu
{
    class VideoDriver;
    class PUNK_ENGINE_API SkinMesh : public Renderable
	{
	public:
		SkinMesh(VideoDriver* driver);
        virtual ~SkinMesh();
        virtual void Bind(int64_t) override;
        virtual void Unbind() override;
        virtual void Render() override;
        bool Cook(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature);
        bool HasData();

    private:
        SkinMesh(const SkinMesh&) = delete;
        SkinMesh& operator = (const SkinMesh&) = delete;

        class SkinMeshImpl;
        SkinMeshImpl* impl;
	};
}

#endif	//	_H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
