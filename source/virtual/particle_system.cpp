#include "partical_system.h"

namespace Utility
{
	ParticleSystem::ParticleSystem()
	{									
		m_infinite = true;
		m_particle_life_time = 10;
		m_particle_life_time_div = 1;
		m_particles_count = 100;		
		m_enable_gravity = false;
		m_time_between_emission = 0.1f;
		m_position.Set(0,0,0);
		m_position_div.Set(0.1f, 0.1f, 0.1f);
		m_direction.Set(0,1,0);
		m_velocity.Set(0,10,0);
		m_velocity_div.Set(0.1f, 0.1f, 0.1f);
	}

	struct StaticVertex
		{
			float x, y, z, w;
			float nx, ny, nz, nw;
			float tx, ty, tz, tw;
			float bx, by, bz, bw;				
			float u, v, s, q;
		};

	std::auto_ptr<StaticMesh> ParticleSystem::CookMesh()
	{
		std::auto_ptr<StaticMesh> mesh(new StaticMesh);
		std::vector<StaticVertex> vb(m_particles_count);
		for (int i = 0; i < m_particles_count; i++)
		{
			vb[i].x = m_position.X() + (rand() / (float)RAND_MAX) * m_position_div.X();
			vb[i].y = m_position.Y() + (rand() / (float)RAND_MAX) * m_position_div.Y();
			vb[i].z = m_position.Z() + (rand() / (float)RAND_MAX) * m_position_div.Z();
			vb[i].w = m_time_between_emission * (float)i;

			vb[i].nx = m_velocity.X() + (rand() / (float)RAND_MAX) * m_velocity_div.X();
			vb[i].ny = m_velocity.Y() + (rand() / (float)RAND_MAX) * m_velocity_div.Y();
			vb[i].nz = m_velocity.Z() + (rand() / (float)RAND_MAX) * m_velocity_div.Z();
			vb[i].nw = m_particle_life_time + (rand() / (float)RAND_MAX) * m_particle_life_time_div;
		}

		std::vector<unsigned> ib(m_particles_count);
		for (int i = 0; i < m_particles_count; i++)
		{
			ib[i] = i;
		}
		mesh.reset(new StaticMesh);
		mesh->SetIndexCount(m_particles_count);
		mesh->SetIndexBuffer(&ib[0], sizeof(unsigned)*m_particles_count);		
		mesh->SetVertexCount(m_particles_count);		
		mesh->SetVertexBuffer(&vb[0], sizeof(StaticVertex)*m_particles_count);
		mesh->SetMeshOffset(Math::mat4::CreateIdentity());
		mesh->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE);
		mesh->SetOneVertexSize(sizeof(StaticVertex));		
		mesh->SetPrimitiveType(PRIMITIVE_TYPE_POINT);
		return mesh;
	}
}