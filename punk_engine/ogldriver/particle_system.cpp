/*
	File: ParticleSystem.cpp
	Author: Abramov Nickolai
	Description: Total plagiat
*/

#include "os.h"
#include "particle_system.h"

ParticleSystem::ParticleSystem(int MaxParticles, float BirthRate, const float *pos, unsigned int id) :
maxParticles(MaxParticles),
birthRate(BirthRate),
textureId(id)
{
	particle = new Particle[maxParticles];
	numParticles = 0;
	memcpy(this->pos, pos, sizeof(this->pos));
	lastUpdateTime = 0;
	lastCreateTime = 0;
	srcBlend = GL_SRC_ALPHA;
	dstBlend = GL_ONE;
	memset(particle, 0, sizeof(Particle)*maxParticles);
}

ParticleSystem::~ParticleSystem()
{
	if (particle)
	{
		delete[] particle;
		particle = 0;
	}
}

void ParticleSystem::Draw()
{
	/*glPushAttrib(GL_ENABLE_BIT|GL_POINT_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnable(GL_BLEND);
	glBlendFunc(srcBlend, dstBlend);
	float quadratic[] = {1.0f, 0.0f, 0.0f, 0.0f};
	glEnable(GL_POINT_SPRITE);
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic);
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 20.0f);
	glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glPointSize(2*size);
	glBegin(GL_POINTS);
	for (int i = 0; i < maxParticles; i++)
	{
		if (particle[i].alive)
		{
			glColor4fv(particle[i].color);
			glVertex3fv(particle[i].pos);
		}
	}
	glEnd();
	glPopAttrib();*/
}

void ParticleSystem::Update(float delta)
{
	register int i, j;
	for (i = 0; i < maxParticles; i++)
	{
		if (particle[i].alive)
		{
			particle[i].time += delta;
			if (particle[i].time > particle[i].lifeTime)
			{
				particle[i].alive = false;
				continue;
			}
			particle[i].pos[0] += delta*particle[i].velocity[0];
			particle[i].pos[1] += delta*particle[i].velocity[1];
			particle[i].pos[2] += delta*particle[i].velocity[2];
		}
	}
	int newParticles = (int)(delta*birthRate+0.5f);
	for (i = j = 0; i < newParticles; i++)
	{
		while (j < maxParticles && particle[j].alive)
			j++;
		if (j >= maxParticles)
			return;

		particle[j].alive = true;
		particle[j].time = 0;
		particle[j].mass = 1;
		CreateParticle(particle[j]);
	}
}
