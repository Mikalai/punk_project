/*
	File: Fog.h
	Author: Abramov Nickolai
	Description: Wrapper around opengl fog, and i hope extension ext_fog_coord
*/

#ifndef _FOG_H
#define _FOG_H

enum FogType {NO};

class Fog
{
public:
	Fog();
	Fog(const Fog& fog);
	virtual ~Fog();

	void Enable();
	void Disable();
	void SetType(FogType type);
	void SetColor(float r, float g, float b, float a);
	void SetDensity(float density);
	void SetStart(float start);
	void SetEnd(float end);

	FogType GetType() const;
	float* GetColor();
	float GetDensity() const;
	float GetStart() const;
	float GetEnd() const;
private:
	FogType m_type;
	float m_color[4];
	float m_density;
	float m_start;
	float m_end;
};

#endif
#ifndef _FOG
#define _FOG

#include "../PunkEngine/PunkEngine.h"

class TFog : public IFog
{
public:
	TFog();
	TFog(const TFog& fog);
	virtual ~TFog();
	virtual TFog& operator = (const TFog& fog);	

	virtual void Enable();
	virtual void Disable();
	virtual void SetType(FogType type);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetDensity(float density);
	virtual void SetStart(float start);
	virtual void SetEnd(float end);

	virtual FogType GetType() const;
	virtual float* GetColor();
	virtual float GetDensity() const;
	virtual float GetStart() const;
	virtual float GetEnd() const;
private:
	FogType m_type;
	float m_color[4];
	float m_density;
	float m_start;
	float m_end;
};

#endif