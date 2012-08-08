#ifndef _H_PUNK_WEAPON_RENDER
#define _H_PUNK_WEAPON_RENDER

namespace Math { template<class T> class Matrix4x4; }
namespace Utility { class WeaponType; }
namespace Utility { class Camera; }
namespace OpenGL { class RenderContext; }

namespace Render
{
	class WeaponRender
	{
		OpenGL::RenderContext* m_rc;
	public:
		void Render(OpenGL::RenderContext* rc, const Utility::WeaponType* weapon);
	};
}

#endif