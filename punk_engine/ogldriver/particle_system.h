/*
	File: ParticleSystem.h
	Author: Abramov Nickolai
	Description: total plagiat from book
*/

#ifndef _H_PARTICLE_SYSTEM
#define _H_PARTICLE_SYSTEM

struct Particle
{
	float pos[3];
	float color[4];
	float velocity[3];
	float mass;
	float time;
	float lifeTime;
	bool alive;
};

class ParticleSystem
{
protected:
	Particle* particle;
	int maxParticles;
	int numParticles;
	float lastUpdateTime;
	float lastCreateTime;
	float birthRate;
	float size;
	float pos[3];
	int srcBlend; 
	int dstBlend;
	unsigned textureId;
public:
	ParticleSystem(int MaxParticles, float BirthRate, const float* pos, unsigned id = 0);
	virtual ~ParticleSystem();
	void SetTexture(unsigned id) { textureId = id; }
	virtual void Update(float delta);
	virtual void Draw();
	virtual void CreateParticle(Particle&) = 0;
};

#endif //	_H_PARTICLE_SYSTEM