#include "fs_particle.h"
#include "../../../../environment.h"

namespace OpenGL
{
	FragmentShaderParticle::FragmentShaderParticle()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.frag");
	}
}