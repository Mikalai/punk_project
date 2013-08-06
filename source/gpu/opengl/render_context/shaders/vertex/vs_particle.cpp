#include "vs_particle.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		VertexShaderParticle::VertexShaderParticle()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.vert");
		}
	}
}