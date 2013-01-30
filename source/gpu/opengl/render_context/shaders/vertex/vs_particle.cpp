#include "vs_particle.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderParticle::VertexShaderParticle()
			: Shader(SHADER_VERTEX)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.vert");
		}
	}
}