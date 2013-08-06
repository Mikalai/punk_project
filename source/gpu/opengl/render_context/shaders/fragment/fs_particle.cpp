#include "fs_particle.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		FragmentShaderParticle::FragmentShaderParticle()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.frag");
		}
	}
}
