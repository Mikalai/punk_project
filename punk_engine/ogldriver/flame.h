/*
File: Flame.h
*/

#ifndef _H_PARTICLE_SYSTEM_FLAME
#define _H_PARTICLE_SYSTEM_FLAME

#include "particle_system.h"
#include "color_spline.h"

class Flame : public ParticleSystem
{
protected:
	float radius;
	float randCoeff;
	float centerCoeff;
	ColorSpline colors;
public:
	Flame(int MaxParticles, float BirthRate, const float* pos, float r, float r1, float r2) :
	  ParticleSystem(MaxParticles, BirthRate, pos)
	  {
		  radius = r;
		  randCoeff = r1;
		  centerCoeff = r2;
		  size = 15;
		  colors.AddColorAt(0, 0.3f, 1, 0.5f, 0);
		  colors.AddColorAt(0, 0.7f, 1, 2, 0.15f);
		  colors.AddColorAt(1, 1, 0, 1, 0.2f);
		  colors.AddColorAt(1, 0, 0, 1, 0.8f);
		  colors.AddColorAt(1, 0, 0, 0, 1);
	  }

	  virtual void CreateParticle(Particle& p)
	  {
		  p.pos[0] = pos[0] + (rand() / (float)RAND_MAX)*radius;
		  p.pos[1] = pos[1] + (rand() / (float)RAND_MAX)*radius;
		  p.pos[2] = pos[2] + (rand() / (float)RAND_MAX)*radius;
		  p.lifeTime = 1.5;
		  p.velocity[0] = 0;
		  p.velocity[1] = 0;
		  p.velocity[2] = 0;
	  }
	  virtual void Update(float delta)
	  {
		  ParticleSystem::Update(delta);
		  for (register int i = 0; i < maxParticles; i++)
		  {
			  if (!particle[i].alive)
				  continue;

			  float v[] = {(rand() / (float)RAND_MAX)*randCoeff,
				  (rand() / (float)RAND_MAX)*randCoeff,
				  (rand() / (float)RAND_MAX)*randCoeff};

			  v[2] = 1;

			  particle[i].pos[0] += delta*v[0];
			  particle[i].pos[1] += delta*v[1];
			  particle[i].pos[2] += delta*v[2];

			  float d = centerCoeff*delta*(particle[i].pos[2]-pos[2]);
			  float dx = (particle[i].pos[0]-pos[0])*d;
			  float dy = (particle[i].pos[1]-pos[1])*d;
			  particle[i].pos[0] -= dx;
			  particle[i].pos[1] -= dy;

			  colors.ValueAt(particle[i].time / particle[i].lifeTime, particle[i].color);
		  }
	  }
};

#endif	// _PARTICLE_SYSTEM_FLAME
