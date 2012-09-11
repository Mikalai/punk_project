#ifndef _H_PUNK_UTILITY_PARTICLE_SYSTEM
#define _H_PUNK_UTILITY_PARTICLE_SYSTEM

#include "../config.h"
#include "../math/vec3.h"
#include "../utility/decl_property.h"
#include "static_mesh.h"

namespace Utility
{
	struct tagEmitionPoint;
	struct tagEmitionRegion;

	template<class T> class EmitionRegion;

	template<> class EmitionRegion<tagEmitionPoint>
	{
	public:		
		struct InitData
		{
			float m_dir_deviation;
			float m_speed_deviation;
			float m_start_speed;
			Math::vec3 m_axis;
		};

	public:
		EmitionRegion(InitData& data) : m_data(data) {}


	private:
		InitData m_data;
	};

	class PUNK_ENGINE ParticleSystem
	{
	public:
		ParticleSystem();
		PROPERTY(bool, Infinite, m_infinite);
		PROPERTY(float, ParticleLifeTime, m_particle_life_time);
		PROPERTY(float, ParticleLifeTimeDeviation, m_particle_life_time_div);
		PROPERTY(int, ParticleCount, m_particles_count);
		PROPERTY(bool, EnableGravity, m_enable_gravity);
		PROPERTY(float, TimeBetweenEmission, m_time_between_emission);
		PROPERTY(Math::vec3, Position, m_position);
		PROPERTY(Math::vec3, ParticlePositionDeviation, m_position_div);
		PROPERTY(Math::vec3, ParticleStartVelocity, m_velocity);
		PROPERTY(Math::vec3, ParticleStartVelocityDeviation, m_velocity_div);

		std::auto_ptr<StaticMesh> CookMesh();
	private:
		bool m_infinite;
		float m_particle_life_time;
		float m_particle_life_time_div;
		int m_particles_count;
		bool m_enable_gravity;
		float m_time_between_emission;
		Math::vec3 m_position;
		Math::vec3 m_position_div;
		Math::vec3 m_velocity;
		Math::vec3 m_velocity_div;
		Math::vec3 m_direction;
	};
}

#endif